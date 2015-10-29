#include "TWIP.h"

using namespace Eigen;

TWIP::TWIP(const unsigned int gyro_port, 
     const unsigned int accel_port,
     const unsigned int motor_left, 
     const unsigned int motor_right,
     float dt)
     : m_kalman_filter(90.0f, 243.0f, dt),
       m_gyroscope(gyro_port),
       m_accelerometer(accel_port),
       m_motors((1 << (motor_left-1)) | (1 << (motor_right - 1)) ) {

  m_motor_ports[0] = motor_left;
  m_motor_ports[1] = motor_right;
  m_motors.Start();
}

Vector2f TWIP::output(float u) {
  Vector2f y;
  
  m_motors.SetPower(floor(u));
  
  float accel_pitch = Accelerometer::ComputePitchFast(m_accelerometer.Read()) * 180.0f / M_PI;
  
  float fused_pitch = m_kalman_filter.getAngle(accel_pitch, m_gyroscope.Read());
  
  float wheel_position = (m_encoders.ReadCount(m_motor_ports[0]) 
        + m_encoders.ReadCount(m_motor_ports[1]))*0.5f;

  y << fused_pitch,
       wheel_position;

  return y; 
}
