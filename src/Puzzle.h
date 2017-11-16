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

    void addRow(vector<unsigned int> &row);

    const vector<vector<unsigned int>> &getSolution() const;

    const PuzzlePiece &getPieceById(int id) const;

    unsigned long getPieceNumber() const;

private:
    vector<PuzzlePiece> pieces;
    vector<vector<unsigned int>> solution;
};


#endif //PUZZLESOLVER_PUZZLE_H
