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
    // TODO
    if (unused.empty()) {
        if (PuzzleValidator::validate(puzzle, sol)) {
            this->sol = sol;

            return true;
        } else {
            return false;
        }
    }

    for (unsigned int i = 0; i < unused.size(); i++) {
        vector<PuzzlePiece> newUnused = unused;
        PuzzleSolution newSol = sol;

        newSol.addElement(static_cast<unsigned int>(unused.at(i).id));

        newUnused.erase(newUnused.begin() + i);

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
