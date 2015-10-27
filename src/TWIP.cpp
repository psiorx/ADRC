#include "TWIP.h"

using namespace Eigen;

TWIP::TWIP(const unsigned int gyro_port, 
     const unsigned int accel_port,
     const unsigned int motor_left, 
     const unsigned int motor_right)
     : m_gyroscope(gyro_port),
       m_accelerometer(accel_port),
       m_motors((1 << (motor_left-1)) | (1 << (motor_right - 1)) ) {

  m_motor_ports[0] = motor_left;
  m_motor_ports[1] = motor_right;
  m_motors.Start();
}

VectorXf TWIP::output(VectorXf const & u) {
  VectorXf y(5);
  
  m_motors.SetPower(floor(u[0]));
  
  y << m_accelerometer.Read(),
       m_gyroscope.Read(),
       (m_encoders.ReadCount(m_motor_ports[0]) 
        + m_encoders.ReadCount(m_motor_ports[1]))*0.5f;
  
  return y; 
}
