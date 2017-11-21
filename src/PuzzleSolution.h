//
// Created by Tomer Amir on 21/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLESOLUTION_H
#define PUZZLESOLVER_PUZZLESOLUTION_H


#include <vector>
#include "PuzzlePiece.h"

using namespace std;

class PuzzleSolution {
private:
    vector<vector<unsigned int>> sol;

public:
    void addRow(vector<unsigned int> &row);

    const vector<vector<unsigned int>> &getSolution() const;

    unsigned long size() const;

    bool empty() const;

    vector<unsigned int> &row(int num) const;
};


#endif //PUZZLESOLVER_PUZZLESOLUTION_H
