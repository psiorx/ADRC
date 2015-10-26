#include <iostream>
#include "gyroscope.h"
#include "accelerometer.h"
#include "Kalman.h"

using namespace std;
using namespace Eigen;

int main()
{
  Gyroscope gyro(1);
  Accelerometer accel(2);
  
  cout << gyro.Calibrate(500) << endl;
  Kalman kalman_filter;

  for(int x = 0; x< 50000; x++) {
    float pitch_accel = Accelerometer::ComputePitchFast(accel.Read()) * 180 / M_PI;
  	float pitch = kalman_filter.getAngle(pitch_accel, gyro.Read(), 0.01f);
  	cout << pitch << endl;
  }

  return 0;
}
