#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "lms2012.h"

class Gyroscope {
  int m_file;
  char m_port;
  ANALOG *m_p_device;
public:
  Gyroscope(const unsigned int port);
  ~Gyroscope();
  float read();
  float calibrate(const unsigned int samples);
};

#endif