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

int main(int argc, char* argv[])
{
  const float dt = 0.01;
  const float u_max = 100.0f;
  const float u_min = -100.0f;
  
  if(argc != 7) {
    cout << "Usage: balance wo_inner wc_inner b0_inner wo_outer wc_outer b0_outer" << endl;
    return 1;
  }
  
  const float wo_inner = atof(argv[1]);
  const float wc_inner = atof(argv[2]);
  const float b0_inner = atof(argv[3]);

  const float wo_outer = atof(argv[4]);
  const float wc_outer = atof(argv[5]);
  const float b0_outer = atof(argv[6]);

  TWIP robot(GYRO_PORT, ACCEL_PORT, MOTOR_LEFT, MOTOR_RIGHT, dt);
  
  Vector2f y;
  float u = 0.0f;

  float wheel_setpoint = 0.0f;
  float angle_setpoint = 0.0f;

  ADRC inner_loop(wo_inner, wc_inner, b0_inner, dt);
  ADRC outer_loop(wo_outer, wc_outer, b0_outer, dt);

  while(true) {
    y = robot.output(u);
    angle_setpoint = outer_loop.Update(angle_setpoint, y[1], wheel_setpoint);
  	u = inner_loop.Update(u, y[0], angle_setpoint);
  	u = max(min(u, u_max), u_min);  	
    usleep(10000);
  }

  return 0;
}
