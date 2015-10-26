#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "lms2012.h"
#include <Eigen/Dense>

class Accelerometer {
  int m_file;
  char m_port;
  IIC *m_p_device;
  IICDAT m_iic_dat;

public:
  Accelerometer(const unsigned int port);
  ~Accelerometer();
  float ReadAxis(const unsigned int axis);
  
  //returns accelerations in g's
  Eigen::Vector3f Read();
 
  //angles in radians
  static float ComputePitchFast(Eigen::Vector3f const & accel);
  static float ComputePitch(Eigen::Vector3f const & accel);
  static float ComputeRoll(Eigen::Vector3f const & accel);
};

#endif