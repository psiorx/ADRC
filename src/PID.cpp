#include "PID.h"

PID::PID(float kp, float ki, float kd, float dt) 
: m_kp(kp), m_ki(ki), m_kd(kd), m_dt(dt) {
  m_last_err = 0.0f;
  m_integrator = 0.0f;
}

float PID::Update(float err) {
  float dedt = (err - m_last_err) / m_dt;
  m_integrator += err * m_dt;  
  m_last_err = err;

  return m_kp * err + m_kd * dedt + m_ki * m_integrator;
}
