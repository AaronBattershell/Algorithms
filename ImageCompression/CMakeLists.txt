project(SVD CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
set(CMAKE_BUILD_TYPE Debug)

set(EIGEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/eigen3/cmake)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(EIGEN3_INCLUDE_DIR)

find_package(Eigen3 REQUIRED)

add_executable(matrix
	main.cpp
	RedSVD.hpp
)
