#ifndef ENCODERS_H
#define ENCODERS_H

#include "lms2012.h"

class Encoders {
  int m_file;
  MOTORDATA *m_p_device;
public:
  Encoders();
  ~Encoders();
  int ReadCount(const unsigned int port);
  int ReadSpeed(const unsigned int port);
};

#endif