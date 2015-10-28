#include "ESO.h"
#include <unsupported/Eigen/MatrixFunctions>

using namespace Eigen;

ESO::ESO(float wo, float b, float dt) {
	SetParameters(wo, b, dt);
}

void ESO::SetParameters(float wo, float b, float dt) {
	Matrix3f A;
	Vector3f B;
	Vector3f L;
	Matrix<float, 1, 3> C;
	Matrix<float, 3, 2> B_obs_ct;
	Matrix3f A_obs_ct;

	A << 0, 1, 0, 0, 0, 1, 0, 0, 0;
	B << 0, b, 0;
	C << 1, 0, 0;
	
	L << 3*wo, 3*wo*wo, wo*wo*wo;
	
	A_obs_ct = A - L * C;
	B_obs_ct << B, L;

	Discretize(A_obs_ct, B_obs_ct, dt);

}

void ESO::Discretize(Matrix3f const & A_obs_ct, 
	Matrix<float, 3, 2> const & B_obs_ct, float dt) {
	Matrix<float, 5, 5> discretization, discretization_exp;

	discretization << A_obs_ct, B_obs_ct, MatrixXf::Zero(2, 5);
	discretization_exp = (discretization*dt).exp();

	A_obs_dt = discretization_exp.block<3, 3>(0, 0);
	B_obs_dt = discretization_exp.block<3, 2>(0, 3);
}

void ESO::SetInitialState(Eigen::Vector3f const & xhat_0) {
	xhat = xhat_0;
}
	

Vector3f ESO::Update(float u, float y) {
	Vector2f u_obs;
	u_obs << u, y;
	xhat = A_obs_dt * xhat + B_obs_dt * u_obs;
	return xhat;
}
