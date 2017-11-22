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

class Edges {
public:
    set<int> left, top, right, bottom;

    void removePiece(int id);
};

class PuzzleSolver {
private:
    Puzzle puzzle;
    PuzzleSolution sol;
    set<int> rowLengths;

    bool solve(PuzzleSolution sol, vector<PuzzlePiece> unused, Edges edges);

    bool checkNewPiece(const vector<vector<unsigned int>> &sol, const PuzzlePiece &piece);

    int addNextElement(int last, PuzzleSolution &sol, vector<PuzzlePiece> &unused, Edges &edges);

    bool sumEdges(const vector<unsigned int> &lastRow, vector<PuzzlePiece> &pieces);

public:
    PuzzleSolver(const Puzzle &puzzle);

    bool solve();

    const PuzzleSolution &getSol() const;

    Edges getEdges();
};


#endif //PUZZLESOLVER_PUZZLESOLVER_H
