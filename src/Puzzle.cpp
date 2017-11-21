//
// Created by Tomer Amir on 12/11/2017.
//

#include <algorithm>
#include "Puzzle.h"

bool compare(const PuzzlePiece &piece1, const PuzzlePiece &piece2)
{
    return piece1.id < piece2.id;
}

Puzzle::Puzzle(vector<PuzzlePiece> newPieces): pieces(move(newPieces))
{
    sort(pieces.begin(), pieces.end(), compare);
}

const PuzzlePiece &Puzzle::getPieceById(int id) const {
    const auto &res = pieces.at(id - 1);
    return res;
}

unsigned long Puzzle::getPieceNumber() const {
    return pieces.size();
}

vector<PuzzlePiece> Puzzle::getPieces() {
    return this->pieces;
}
