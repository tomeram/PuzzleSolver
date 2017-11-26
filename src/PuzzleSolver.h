//
// Created by Tomer Amir on 21/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLESOLVER_H
#define PUZZLESOLVER_PUZZLESOLVER_H

#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

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
    bool valid = true;
    Puzzle puzzle;
    ofstream *out;
    PuzzleSolution sol;
    set<int> rowLengths;
    map<string, vector<int>> types;

    bool solve(PuzzleSolution sol, vector<PuzzlePiece> unused, Edges edges, map<string, vector<int>> types);

    bool checkNewPiece(const vector<vector<unsigned int>> &sol, const PuzzlePiece &piece);

    vector<string> addNextElement(PuzzleSolution sol, vector<PuzzlePiece> unused, Edges edges,
                               map<string, vector<int>> types);

    bool checkRowCol();

    void checkCorners();

    void checkInput();

    bool sumEdges(const vector<unsigned int> &lastRow, vector<PuzzlePiece> &pieces);

public:
    PuzzleSolver(const Puzzle &puzzle, ofstream *output);

    bool isValid() {
        return valid;
    }

    bool solve();

    const PuzzleSolution &getSol() const;

    Edges getEdges();
};


#endif //PUZZLESOLVER_PUZZLESOLVER_H
