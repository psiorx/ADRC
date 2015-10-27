#include "Motor.h"
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

using namespace std;

Motor::Motor(const unsigned char port) : m_port(port) {

  m_file = open(PWM_DEVICE_NAME, O_WRONLY);

  if(m_file == -1) {
    cout << "Error: couldn't open the pwm device." << endl;
    return;
  }

  m_motor_command[1] = port;
}

Motor::~Motor() {
  if(m_file != -1) {
    close(m_file);
  }
}

void Motor::Start() {
  m_motor_command[0] = opOUTPUT_START;
  write(m_file, m_motor_command, 2);  
}

void Motor::Stop() {
  m_motor_command[0] = opOUTPUT_STOP;
  write(m_file, m_motor_command, 2);  
}


void Motor::SetPower(int power) {
  if(power > 100) {
    power = 100;
  } else if (power < -100) {
    power = -100;
  }

  m_motor_command[0] = opOUTPUT_POWER; 
  m_motor_command[2] = static_cast<char>(power);
  write(m_file, m_motor_command,3);
}
