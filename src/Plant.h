#ifndef PLANT_H
#define PLANT_H

#include <Eigen/Dense>

class Plant {
public:
  Plant() {};
  virtual ~Plant() {};
  virtual Eigen::VectorXf output(Eigen::VectorXf const & u) = 0;
  Eigen::VectorXf output(float u) {
    Eigen::VectorXf u_vec(1);
    u_vec << u;
    return output(u_vec);
  }
};

#endif