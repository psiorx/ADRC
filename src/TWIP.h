#ifndef TWIP_H
#define TWIP_H

#include "Plant.h"
#include "Gyroscope.h"
#include "Accelerometer.h"
#include "Motor.h"
#include "Encoders.h"

// TWIP: Two Wheeled Inverted Pendulum

class TWIP : public Plant {
	Gyroscope m_gyroscope;
	Accelerometer m_accelerometer;
	Motor m_motors;
	Encoders m_encoders;

	unsigned int m_motor_ports[2];

public:
  TWIP(const unsigned int gyro_port, 
  	   const unsigned int accel_port,
       const unsigned int motor_left, 
       const unsigned int motor_right);
  virtual ~TWIP() {};
  virtual Eigen::VectorXf output(Eigen::VectorXf const & u);
};

#endif