#include "Encoders.h"
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

using namespace std;

Encoders::Encoders() {

  m_file = open(MOTOR_DEVICE_NAME, O_RDWR | O_SYNC);

  if(m_file == -1) {
    cout << "Error: couldn't open the analog device." << endl;
    return;
  }

  m_p_device = (MOTORDATA*)mmap(0, sizeof(MOTORDATA)*vmOUTPUTS, 
    PROT_READ | PROT_WRITE, 
    MAP_FILE | MAP_SHARED, m_file, 0);

  if(m_p_device == MAP_FAILED) {
    cout << "Error: failed to map the analog device." << endl;
  }
}

Encoders::~Encoders() {
  if(m_file != -1) {
    close(m_file);
  }
}

int Encoders::ReadCount(const unsigned int port) const {
  return m_p_device[port].TachoSensor;
}

int Encoders::ReadSpeed(const unsigned int port) const {
  return m_p_device[port].Speed;
}
