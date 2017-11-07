cmake_minimum_required(VERSION 3.8)
project(PazzleSolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp PazzlePeice.cpp PazzlePeice.h InputReader.cpp InputReader.h)
add_executable(PazzleSolver ${SOURCE_FILES})