//
// Created by Tomer Amir on 21/11/2017.
//

#include "PuzzleSolver.h"
#include "PuzzleValidator.h"

PuzzleSolver::PuzzleSolver(const Puzzle &puzzle) : puzzle(puzzle)
{
    int size = static_cast<int>(puzzle.getPieces().size());
    for (int i = 1; i <= size; i++) {
        if (size % i == 0) {
            rowLengths.insert(i);
        }
    }
}

bool PuzzleSolver::solve() {
    return this->solve(PuzzleSolution(), this->puzzle.getPieces());
}

bool PuzzleSolver::solve(PuzzleSolution sol, vector<PuzzlePiece> unused) {
    // TODO: Remove comments
//    static int calls = 0;
//
//    calls++;
//
//    cout << "Call: " << calls << endl;

    if (unused.empty()) {
        if (PuzzleValidator::validate(puzzle, sol)) {
            this->sol = sol;

            return true;
        } else {
            return false;
        }
    }

    int last = -1;

    for (unsigned int i = 0; i < unused.size(); i++) {
        vector<PuzzlePiece> newUnused = unused;
        PuzzleSolution newSol = sol;

        if ((last = addNextElement(last, newSol, newUnused)) == -1) {
            break;
        }

        // TODO: Remove comments
//        newSol.addElement(static_cast<unsigned int>(unused.at(i).id));
//
//        newUnused.erase(newUnused.begin() + i);

        if (this->solve(newSol, newUnused)) {
            return true;
        }
    }

    auto currRow = static_cast<int>(sol.getSolution().size()) - 1;
    unsigned int currRowSize = sol.getSolution().at(currRow).size();
    auto search = rowLengths.find(currRowSize);

    if (search != rowLengths.end()) {
        if (currRow != 0 && (sol.getSolution().at(currRow - 1).size() != currRowSize)) {
            return false;
        }

        PuzzleSolution newRowSol = sol;
        newRowSol.addRow();

        if (this->solve(newRowSol, unused)) {
            return true;
        }
    }

    return false;
}

const PuzzleSolution &PuzzleSolver::getSol() const {
    return sol;
}

int PuzzleSolver::addNextElement(int last, PuzzleSolution &sol, vector<PuzzlePiece> &unused) {

    auto matrix = sol.getSolution();
    auto size = matrix.size();

    if (matrix.size() > 1) {
        if (matrix.at(size - 1).size() == matrix.at(size - 2).size()) {
            return -1;
        }
    }

    for (unsigned int i = last + 1; i < unused.size(); i++) {
        PuzzlePiece &elem = unused.at(i);

        bool accepted = checkNewPiece(sol.getSolution(), elem);

        // TODO: Check elem
        if (accepted) {
            sol.addElement(static_cast<unsigned int>(elem.id));

            unused.erase(unused.begin() + i);

            return i;
        }
    }

    return -1;
}

bool PuzzleSolver::checkNewPiece(const vector<vector<unsigned int>> &sol, const PuzzlePiece &piece) {
    int row = sol.size() - 1;
    int col = sol.at(row).size();

    // Top
    if (row > 0) {
        auto &top = puzzle.getPieceById(sol.at(row - 1).at(col));

        if (top.b + piece.t != 0) {
            return false;
        }
    } else {
        if (piece.t != 0) {
            return false;
        }
    }

    // Left
    if (col > 0) {
        auto &left = puzzle.getPieceById(sol.at(row).at(col - 1));

        if (left.r + piece.l != 0) {
            return false;
        }
    } else {
        if (piece.l != 0) {
            return false;
        }
    }

    return true;
}
