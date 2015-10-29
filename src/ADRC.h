#ifndef ADRC_H
#define ADRC_H

#include <Eigen/Core>
#include "ESO.h"

class ADRC {
	ESO m_observer;
	float m_kp;
	float m_kd;
	float m_b;

	float Controller(Eigen::Vector3f const & xhat, float y_desired);
public:
	ADRC(float wo, float wc, float b, float dt);
	virtual ~ADRC() { };
	float Update(float u, float y, float y_desired);
};

#endif