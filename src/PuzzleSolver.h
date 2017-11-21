//
// Created by Tomer Amir on 21/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLESOLVER_H
#define PUZZLESOLVER_PUZZLESOLVER_H

#include <vector>
#include <string>
#include <set>

#include "Puzzle.h"
#include "PuzzleSolution.h"

using namespace std;

class PuzzleSolver {
private:
    Puzzle puzzle;
    PuzzleSolution sol;
    vector<string> exceptions;

    bool solve(PuzzleSolution sol, vector<PuzzlePiece> unused);
    set<int> rowLengths;

public:
    PuzzleSolver(const Puzzle &puzzle);

    bool solve();

    const PuzzleSolution &getSol() const;
};


#endif //PUZZLESOLVER_PUZZLESOLVER_H
