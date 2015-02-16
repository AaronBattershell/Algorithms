project(watchman CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
set(CMAKE_BUILD_TYPE Debug)

add_executable(matrix
	main.cpp
	RedSVD.hpp
)