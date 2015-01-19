project(watchman CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)

add_executable(watchman
	main.cpp
	graph.hpp
	graph.cpp
	bfs.hpp
	bfs.cpp
	parsing.hpp
	parsing.cpp
	intersection.hpp
	intersection.cpp
)
