#ifndef ADRC_H
#define ADRC_H

#include <Eigen/Core>

class ADRC {
	float Controller(Eigen::Vector3f const & xhat, float y_desired);
public:
	ADRC(float wo, float wc, float b);
	virtual ~ADRC() { };
	float Update(float u, float y, float y_desired);
};

#endif