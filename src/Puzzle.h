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

    const PuzzlePiece &getPieceById(int id) const;

    unsigned long getPieceNumber() const;

    vector<PuzzlePiece> getPieces();

private:
    vector<PuzzlePiece> pieces;
};


#endif //PUZZLESOLVER_PUZZLE_H
