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
    PuzzlePiece* readInput(string path);
};


#endif //PUZZLESOLVER_INPUTREADER_H
