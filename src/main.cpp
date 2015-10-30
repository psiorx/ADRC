#include <iostream>
#include "ADRC.h"
#include "TWIP.h"
#include "Motor.h"

#define GYRO_PORT 1
#define ACCEL_PORT 2
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 4

using namespace std;
using namespace Eigen;

int main()
{
  //const float dt = 1/561.0f;
  const float dt = 0.01;
  const float wo_inner = 40.0f;
  const float wc_inner = 5.0f;
  const float b_inner = 100.0f;
  const float u_min = -100.0f;
  const float u_max = 100.0f;

  TWIP robot(GYRO_PORT, ACCEL_PORT, MOTOR_LEFT, MOTOR_RIGHT, dt);
  
  Vector2f y(0,0);
  float u = 0.0f;

  ADRC inner_loop(wo_inner, wc_inner, b_inner, dt);

  for(int x=0;x<100000;x++) {
  	y = robot.output(u);
  	u = inner_loop.Update(u, y[1], 360);
  	u = max(min(u, u_max), u_min);
  	cout << y[1] << endl;
  	usleep(10000);
  }

  return 0;
}
