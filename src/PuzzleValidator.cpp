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
        cout << "Top" << endl;
        return false;
    }

    // Check last row
    if (row == rows - 1 && piece.b != 0) {
        cout << "Bottom" << endl;
        return false;
    }

    // First piece in row
    if (col == 0 && piece.l != 0) {
        cout << "Left" << endl;
        return false;
    }

    // Last piece in row
    if (col == cols - 1 && piece.r != 0) {
        cout << "Right" << endl;
        return false;
    }

    return true;
}

bool checkUsedPieces(vector<unsigned int> &usedPieces, unsigned int pieceNum)
{
    sort(usedPieces.begin(), usedPieces.end());

    if (usedPieces.size() != pieceNum) {
        cout << "There are Unused pieces" << endl;
        return false;
    }

    for (unsigned int i = 0; i < usedPieces.size(); i++) {
        if (i + 1 != usedPieces.at(i)) {
            cout << "Duplicate piece used" << endl;
            return false;
        }
    }

    return true;
}

bool PuzzleValidator::validate(const Puzzle &puzzle)
{
    auto &sol = puzzle.getSolution();

    if (sol.empty()) {
        return false;
    }

    // Check row size to make sure all rows have the same size
    auto rowSize = static_cast<unsigned int>(sol.at(0).size());
    vector<unsigned int> usedPieces;

    for (unsigned int i = 0; i < sol.size(); i++) {
        auto &row = sol[i];

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
                auto &top = puzzle.getPieceById(sol.at(i - 1).at(j));

                if (top.b + piece.t != 0) {
                    cout << "top" << endl;
                    return false;
                }
            }

            // Bottom
            if (i < sol.size() - 1) {
                auto &bot = puzzle.getPieceById(sol.at(i + 1).at(j));

                if (bot.t + piece.b != 0) {
                    cout << "bot" << endl;
                    return false;
                }
            }

            // Left
            if (j > 0) {
                auto &left = puzzle.getPieceById(sol.at(i).at(j - 1));

                if (left.r + piece.l != 0) {
                    cout << "left" << endl;
                    return false;
                }
            }

            // Right
            if (j < rowSize - 1) {
                auto &right = puzzle.getPieceById(sol.at(i).at(j + 1));

                if (right.l + piece.r != 0) {
                    cout << "right" << endl;
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
