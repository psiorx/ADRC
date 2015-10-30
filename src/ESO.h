#ifndef ESO_H
#define ESO_H

#include <Eigen/Core>

class ESO {
	Eigen::Vector3f m_xhat;
	Eigen::Matrix3f m_A_obs_dt;
	Eigen::Matrix<float, 3, 2> m_B_obs_dt;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	void Discretize(Eigen::Matrix3f const & A_obs_ct, 
	Eigen::Matrix<float, 3, 2> const & B_obs_ct, float dt);
public:
	ESO(float wo, float b0, float dt);
	virtual ~ESO() { };
	void SetState(Eigen::Vector3f const & xhat);
	void SetParameters(float wo, float b, float dt);
	Eigen::Vector3f Update(float u, float y);
};

#endif