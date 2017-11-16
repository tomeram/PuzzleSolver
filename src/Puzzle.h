//
// Created by Tomer Amir on 12/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLE_H
#define PUZZLESOLVER_PUZZLE_H

#include <vector>
#include "PuzzlePiece.h"

using namespace std;

class Puzzle {
public:
    explicit Puzzle(vector<PuzzlePiece> pieces);

    ~Puzzle() = default;

    void addRow(vector<int> &row);

    const vector<vector<int>> &getSolution() const;

    const PuzzlePiece &getPieceById(int id) const;

    unsigned long getPieceNumber() const;

private:
    vector<PuzzlePiece> pieces;
    vector<vector<int>> solution;
};


#endif //PUZZLESOLVER_PUZZLE_H
