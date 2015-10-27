project(adrc_balance)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_COMPILER arm-none-linux-gnueabi-g++)

set(CMAKE_CXX_FLAGS "-std=c++0x -static -O3")

find_package(Eigen3 REQUIRED)

include_directories(KalmanFilter)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(balance 
  src/main.cpp 
  src/Gyroscope.cpp 
  src/Accelerometer.cpp 
  src/Motor.cpp 
  src/Encoders.cpp
  KalmanFilter/Kalman.cpp
)
