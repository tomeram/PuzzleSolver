//
// Created by Tomer Amir on 21/11/2017.
//

#include "PuzzleSolution.h"

void PuzzleSolution::addRow(vector<unsigned int> &row)
{
    this->sol.push_back(row);
}

const vector<vector<unsigned int>> &PuzzleSolution::getSolution() const
{
    return this->sol;
}

bool PuzzleSolution::empty() const {
    return this->sol.empty();
}

vector<unsigned int> &PuzzleSolution::row(int num) const {
    return const_cast<vector<unsigned int> &>(sol.at(num));
}

unsigned long PuzzleSolution::size() const {
    return sol.size();
}
