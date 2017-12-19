//
// Created by Tomer Amir on 21/11/2017.
//

#include "PuzzleSolution.h"

PuzzleSolution::PuzzleSolution()
{
    addRow();
}

void PuzzleSolution::addRow()
{
    this->sol.emplace_back();
}

void PuzzleSolution::addElement(unsigned int id)
{
    sol.back().push_back(id);
}

const vector<vector<unsigned int>> &PuzzleSolution::getSolution() const
{
    return this->sol;
}

bool PuzzleSolution::empty() const {
    return this->sol.empty();
}

vector<unsigned int> &PuzzleSolution::row(int num) const
{
    return const_cast<vector<unsigned int> &>(sol.at(num));
}

unsigned long PuzzleSolution::size() const {
    return sol.size();
}

void PuzzleSolution::print(ofstream *out, bool rotate, Puzzle &puzzle) const
{
    for (auto row: sol) {
        for (unsigned int i = 0; i < row.size(); i++) {
			auto pieceID = row.at(i);
            *out << pieceID;

			if (rotate) {
				auto pieceRotation = puzzle.getPieceById(pieceID).getRotation();

				if (!pieceRotation.empty()) {
					*out << " [" << pieceRotation << "]";
				}
			}

            if (i < row.size() - 1) {
                *out << " ";
            }
        }

        *out << endl;
    }
}
