#include <iostream>
#include "ADRC.h"
#include "TWIP.h"

#define GYRO_PORT 1
#define ACCEL_PORT 2
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 4

using namespace std;
using namespace Eigen;

int main()
{
  const float dt = 0.01f;

  const float wo_inner = 150.0f;
  const float wc_inner = 15.0f;
  const float b_inner = 100.0f;

  TWIP robot(GYRO_PORT, ACCEL_PORT, MOTOR_LEFT, MOTOR_RIGHT, dt);
  
  VectorXf y(5);
  float u = 0.0f;

  ADRC inner_loop(wo_inner, wc_inner, b_inner, dt);

  while(true) {
  	y = robot.output(u);
  	u = inner_loop.Update(u, y[0], 0.0f);
  }

  return 0;
}
