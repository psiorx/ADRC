#ifndef PID_H
#define PID_H

class PID {
	float m_kp;
	float m_ki;
	float m_kd;
	float m_dt;

	float m_integrator;
	float m_last_err;
	
public:
	PID(float kp, float ki, float kd, float dt);
	float Update(float err);
};

#endif