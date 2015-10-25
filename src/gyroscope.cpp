#include "gyroscope.h"
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

using namespace std;

Gyroscope::Gyroscope(const unsigned int port) {
  if(port > 4) {
    cout << "Error: gyroscope port must be an integer in the range [0, 4]" << endl;
    return;
  }

  m_port = (char) (port - 1);

  m_file = open(ANALOG_DEVICE_NAME, O_RDWR | O_SYNC);

  if(m_file == -1) {
    cout << "Error: couldn't open the analog device." << endl;
    return;
  }

  m_p_device = (ANALOG*)mmap(0, sizeof(ANALOG), 
    PROT_READ | 
    PROT_WRITE, 
    MAP_FILE | 
    MAP_SHARED, m_file, 0);

  if(m_p_device == MAP_FAILED) {
    cout << "Error: failed to map the analog device." << endl;
  }
}

Gyroscope::~Gyroscope() {
  if(m_file != -1) {
    close(m_file);
  }
}

float Gyroscope::read() {
  DATA16 raw = m_p_device->Pin1[m_port][m_p_device->Actual[m_port]];
  return ((float) raw) / 10.0f;
}

float Gyroscope::calibrate(const unsigned int samples) {
  if(samples == 0) {
    cout << "Error: calibration requires at least one sample." << endl;
    return 0.0f;
  }

  float sum = 0.0f;
  
  for(int i = 0; i < samples; i++) {
    sum += read();
  }
  
  return sum / samples;
}