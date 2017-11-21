//
// Created by Tomer Amir on 07/11/2017.
//

#ifndef PUZZLESOLVER_INPUTREADER_H
#define PUZZLESOLVER_INPUTREADER_H


#include "PuzzlePiece.h"

#include <string>

using namespace std;

class InputReader {
public:
    static void readInput(string path, vector<PuzzlePiece> &pieces) throw(int);
};


#endif //PUZZLESOLVER_INPUTREADER_H
