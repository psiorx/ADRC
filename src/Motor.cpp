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
  WriteCommand(2);
}

void Motor::Stop() {
  m_motor_command[0] = opOUTPUT_STOP;
  WriteCommand(2);
}

void Motor::Reset() {
  m_motor_command[0] = opOUTPUT_RESET;
  WriteCommand(2);
}

void Motor::WriteCommand(const unsigned int bytes) {
  write(m_file, m_motor_command, bytes);
}

void Motor::SetPower(int power) {
  m_motor_command[0] = opOUTPUT_POWER; 
  m_motor_command[2] = static_cast<char>(power);
  WriteCommand(3);
}
