//
// Created by Tomer Amir on 12/11/2017.
//

#include <algorithm>
#include "Puzzle.h"

Puzzle::Puzzle(vector<PuzzlePiece> newPieces): pieces(newPieces)
{
    sort(pieces.begin(), pieces.end(), PuzzlePiece::compare);
}

PuzzlePiece &Puzzle::getPieceById(int id) {;
    return pieces.at(id - 1);
}

unsigned long Puzzle::getPieceNumber() const {
    return pieces.size();
}

vector<PuzzlePiece> Puzzle::getPieces() const
{
    return this->pieces;
}

int Puzzle::size() {
	return pieces.size();
}
