cmake_minimum_required(VERSION 3.6)
project(PuzzleSolver)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic-errors -DNDEBUG -static")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic-errors -DNDEBUG")
endif (WIN32)

set(SOURCE_FILES src/main.cpp src/PuzzlePiece.cpp src/PuzzlePiece.h src/InputReader.cpp src/InputReader.h src/PuzzleValidator.cpp src/PuzzleValidator.h src/Puzzle.cpp src/Puzzle.h src/PuzzleSolution.cpp src/PuzzleSolution.h src/PuzzleSolver.cpp src/PuzzleSolver.h src/TypesMap.cpp src/TypesMap.h)
add_executable(PuzzleSolver ${SOURCE_FILES})