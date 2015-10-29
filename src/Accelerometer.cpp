#include "Accelerometer.h"
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cmath>

using namespace Eigen;
using namespace std;

Accelerometer::Accelerometer(const unsigned int port) {
  if(port == 0 || port > 4) {
    cout << "Error: accelerometer port must be an integer in the range [1, 4]" << endl;
    return;
  }

  m_port = port - 1;

  m_file = open(IIC_DEVICE_NAME, O_RDWR | O_SYNC);

  if(m_file == -1) {
    cout << "Error: couldn't open the i2c device." << endl;
    return;
  }

  m_p_device = (IIC*)mmap(0, sizeof(IIC), 
    PROT_READ | PROT_WRITE, 
    MAP_FILE | MAP_SHARED, m_file, 0);

  if(m_p_device == MAP_FAILED) {
    cout << "Error: failed to map the i2c device." << endl;
  }

  m_iic_dat.Port = m_port;
  m_iic_dat.Time = 0;
  m_iic_dat.Repeat = 0;
  m_iic_dat.RdLng = 6;
  m_iic_dat.WrLng = 2;
  m_iic_dat.WrData[0] = 0x01;
  m_iic_dat.WrData[1] = 0x42;
  ioctl(m_file, IIC_SETUP, &m_iic_dat);
}

Accelerometer::~Accelerometer() {
  if(m_file != -1) {
    close(m_file);
  }
}

float Accelerometer::ReadAxis(const unsigned int axis) {
  int accel = m_p_device->Raw[m_port][m_p_device->Actual[m_port]][axis+3];
  accel <<= 2;
  accel |= m_p_device->Raw[m_port][m_p_device->Actual[m_port]][axis];
  return accel/200.0f;
}

Vector3f Accelerometer::Read() {
  Vector3f acceleration;
  acceleration << ReadAxis(2), ReadAxis(1), ReadAxis(0);
  return acceleration;
}

float Accelerometer::ComputePitchFast(Eigen::Vector3f const & accel) {
  return atan2(accel[1], accel[0]);
}

float Accelerometer::ComputePitch(Eigen::Vector3f const & accel) {
  return atan2(accel[1], sqrt(accel[0] * accel[0] + accel[2] * accel[2]));
}

float Accelerometer::ComputeRoll(Eigen::Vector3f const & accel) {
  return atan2(-accel[0], accel[2])*(180/M_PI);
}