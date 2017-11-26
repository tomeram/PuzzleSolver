//
// Created by Tomer Amir on 12/11/2017.
//

#include "PuzzleValidator.h"

#include <algorithm>

using namespace std;

bool checkPuzzleEdges(const PuzzlePiece &piece, int row, int col, int cols, int rows)
{
    // Check first row
    if (row == 0 && piece.t != 0) {
        return false;
    }

    // Check last row
    if (row == rows - 1 && piece.b != 0) {
        return false;
    }

    // First piece in row
    if (col == 0 && piece.l != 0) {
        return false;
    }

    // Last piece in row
    if (col == cols - 1 && piece.r != 0) {
        return false;
    }

    return true;
}

bool checkUsedPieces(vector<unsigned int> &usedPieces, unsigned int pieceNum)
{
    sort(usedPieces.begin(), usedPieces.end());

    if (usedPieces.size() != pieceNum) {
        return false;
    }

    for (unsigned int i = 0; i < usedPieces.size(); i++) {
        if (i + 1 != usedPieces.at(i)) {
            return false;
        }
    }

    return true;
}

bool PuzzleValidator::validate(const Puzzle &puzzle, const PuzzleSolution &sol)
{
    if (sol.empty()) {
        return false;
    }

    // Check row size to make sure all rows have the same size
    auto rowSize = static_cast<unsigned int>(sol.row(0).size());
    vector<unsigned int> usedPieces;

    for (unsigned int i = 0; i < sol.size(); i++) {
        auto &row = sol.row(i);

        // Make sure all rows have the same size
        if (row.size() != rowSize) {
            return false;
        }

        for (unsigned int j = 0; j < rowSize; j++) {
            unsigned int pieceID = row[j];

            usedPieces.push_back(pieceID);
            auto &piece = puzzle.getPieceById(pieceID);

            if (!checkPuzzleEdges(piece, i, j, rowSize, static_cast<int>(sol.size()))) {
                return false;
            }

            /***** Check Neighbors *****/
            // Top
            if (i > 0) {
                auto &top = puzzle.getPieceById(sol.row(i - 1).at(j));

                if (top.b + piece.t != 0) {
                    return false;
                }
            }

            // Bottom
            if (i < sol.size() - 1) {
                auto &bot = puzzle.getPieceById(sol.row(i + 1).at(j));

                if (bot.t + piece.b != 0) {
                    return false;
                }
            }

            // Left
            if (j > 0) {
                auto &left = puzzle.getPieceById(sol.row(i).at(j - 1));

                if (left.r + piece.l != 0) {
                    return false;
                }
            }

            // Right
            if (j < rowSize - 1) {
                auto &right = puzzle.getPieceById(sol.row(i).at(j + 1));

                if (right.l + piece.r != 0) {
                    return false;
                }
            }
        }
    }

    if (!checkUsedPieces(usedPieces, puzzle.getPieceNumber())) {
        return false;
    }

    return true;
}
