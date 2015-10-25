#include "gyroscope.h"
#include <iostream>

using namespace std;

int main() {
  
  Gyroscope gyro(1);

  float bias = gyro.calibrate(500);

  for(int i = 0; i < 50000; i++) {
    cout << (gyro.read() - bias) << endl;
  }

  return 0;
}