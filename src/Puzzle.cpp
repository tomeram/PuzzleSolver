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

const vector<vector<unsigned int>> &Puzzle::getSolution() const
{
    const auto &res = solution;
    return res;
}

void Puzzle::addRow(vector<unsigned int> &row)
{
    this->solution.push_back(move(row));
}

const PuzzlePiece &Puzzle::getPieceById(int id) const {
    const auto &res = pieces.at(id - 1);
    return res;
}

unsigned long Puzzle::getPieceNumber() const {
    return pieces.size();
}
