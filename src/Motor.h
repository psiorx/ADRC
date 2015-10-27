#ifndef MOTOR_H
#define MOTOR_H

#include "lms2012.h"

enum MotorPort {
	PORT_A = 0x01,
	PORT_B = 0x02,
	PORT_C = 0x04,
	PORT_D = 0x08
};

class Motor {
  int m_file;
  char m_port;
  char m_motor_command[3];
public:
  Motor(const unsigned char port);
  ~Motor();
  void SetPower(int power);
  void Start();
  void Stop();
};

#endif