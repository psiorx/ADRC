#include <iostream>
#include "gyroscope.h"
#include "accelerometer.h"

using namespace std;
using namespace Eigen;

int main()
{
  Gyroscope gyro(1);
  Accelerometer accel(2);
  
  cout << gyro.Calibrate() << endl;
  
  for(int x = 0; x< 50000; x++) {
    float pitch = Accelerometer::ComputePitchFast(accel.Read());
    cout << pitch << endl;
  }

  return 0;
}