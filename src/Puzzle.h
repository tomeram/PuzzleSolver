//
// Created by Tomer Amir on 12/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLE_H
#define PUZZLESOLVER_PUZZLE_H

#include <vector>

using namespace std;

class Puzzle {
public:
    Puzzle();
    ~Puzzle();

    void addRow();

private:
    vector<vector<int>> *matrix;
};


#endif //PUZZLESOLVER_PUZZLE_H
