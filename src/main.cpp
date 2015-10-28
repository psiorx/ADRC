#include <iostream>
#include "ADRC.h"
#include "ESO.h"
#include "Kalman.h"
#include "TWIP.h"
#include "CascadePlant.h"

#define GYRO_PORT 1
#define ACCEL_PORT 2
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 4

using namespace std;
using namespace Eigen;

int main()
{
  TWIP robot(GYRO_PORT, ACCEL_PORT, MOTOR_LEFT, MOTOR_RIGHT);

  Kalman kalman_filter(90, 243, 0.01);
  VectorXf y(5);
  VectorXf u(1);
  u << 0.0f;

  for(int x = 0; x< 50000; x++) {
  	y = robot.output(u);
    float accel_pitch = Accelerometer::ComputePitchFast(y.head<3>()) * 180 / M_PI;
  	float pitch = kalman_filter.getAngle(accel_pitch, y[3]);
  	cout << pitch << endl;
  }

  ESO eso(5, 100, 0.01);

  return 0;
}
