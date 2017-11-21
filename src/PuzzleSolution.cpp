//
// Created by Tomer Amir on 21/11/2017.
//

#include <iostream>
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

void PuzzleSolution::print() const
{
    for (auto row: sol) {
        for (auto elem: row) {
            cout << elem << " ";
        }

        cout << endl;
    }
}
