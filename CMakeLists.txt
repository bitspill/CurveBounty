cmake_minimum_required(VERSION 2.8.4)
project(CurveBounty)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -std=c++11")

set(SOURCE_FILES main.cpp uint256_t.h uint256_t.cpp uint128_t.h uint128_t.cpp)
add_executable(CurveBounty ${SOURCE_FILES})