#ifndef MOTOR_H
#define MOTOR_H

#include "lms2012.h"

class Motor {
  int m_file;
  char m_port;
  char m_motor_command[3];
  void WriteCommand(const unsigned int bytes);
public:
  Motor(const unsigned char port);
  ~Motor();
  void SetPower(int power);
  void Start();
  void Stop();
  void Reset();
};

#endif