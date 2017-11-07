//
// Created by Tomer Amir on 07/11/2017.
//

#ifndef PAZZLESOLVER_INPUTREADER_H
#define PAZZLESOLVER_INPUTREADER_H


#include "PazzlePeice.h"

#include <string>

using namespace std;

class InputReader {
public:
    PazzlePeice* readInput(string path);
};


#endif //PAZZLESOLVER_INPUTREADER_H
