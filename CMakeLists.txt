project(adrc_balance)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER   arm-none-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-linux-gnueabi-g++)

add_executable(balance src/main.cpp)
