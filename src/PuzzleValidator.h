//
// Created by Tomer Amir on 12/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLEVALIDATOR_H
#define PUZZLESOLVER_PUZZLEVALIDATOR_H


#include "Puzzle.h"
#include "PuzzleSolution.h"
#include <iostream>
#include <vector>

class PuzzleValidator {
public:
    static bool validate(const Puzzle &puzzle, const PuzzleSolution &sol);
};


#endif //PUZZLESOLVER_PUZZLEVALIDATOR_H
