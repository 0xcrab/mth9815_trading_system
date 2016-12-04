cmake_minimum_required(VERSION 3.6)
PROJECT(test_proj) 
#SET(SRC_LIST src/main.cpp) 
file(GLOB_RECURSE SOURCES "src/*.cpp")
SET(CMAKE_CXX_COMPILER "g++") 
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3") 
SET(CMAKE_BUILD_TYPE Release) 
ADD_EXECUTABLE(hello_world ${SOURCES})

