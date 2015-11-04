#include "TWIP.h"

using namespace Eigen;

TWIP::TWIP(const unsigned int gyro_port, 
     const unsigned int accel_port,
     const unsigned int motor_left, 
     const unsigned int motor_right,
     float dt) :
       m_gyroscope(gyro_port),
       m_kalman_filter(90.0f, m_gyroscope.Calibrate(100), dt),
       m_accelerometer(accel_port),
       m_motors((1 << (motor_left - 1)) | (1 << (motor_right - 1))) {
  
  m_motor_ports[0] = motor_left - 1;
  m_motor_ports[1] = motor_right - 1;

  m_motors.Start();
  m_motors.Reset();

  m_encoder_offset[0] = m_encoders.ReadCount(m_motor_ports[0]);
  m_encoder_offset[1] = m_encoders.ReadCount(m_motor_ports[1]);
}

Vector2f TWIP::output(float u) {

  Vector2f y;

  m_motors.SetPower(u);
  
  float accel_pitch = Accelerometer::ComputePitchFast(m_accelerometer.Read()) * 180.0f / M_PI;
  
  float fused_pitch = m_kalman_filter.getAngle(accel_pitch, m_gyroscope.Read());
  
  int encoder_left = m_encoders.ReadCount(m_motor_ports[0]) - m_encoder_offset[0];  
  int encoder_right = m_encoders.ReadCount(m_motor_ports[1]) - m_encoder_offset[1];

  float wheel_position = (encoder_left + encoder_right) * 0.5f;

  y << fused_pitch,
       wheel_position;

  return y; 
}
