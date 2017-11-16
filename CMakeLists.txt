cmake_minimum_required(VERSION 3.6)
project(PuzzleSolver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG")

set(SOURCE_FILES src/main.cpp src/PuzzlePiece.cpp src/PuzzlePiece.h src/InputReader.cpp src/InputReader.h)
add_executable(PuzzleSolver ${SOURCE_FILES})