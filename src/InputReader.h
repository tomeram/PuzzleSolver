//
// Created by Tomer Amir on 07/11/2017.
//

#ifndef PUZZLESOLVER_INPUTREADER_H
#define PUZZLESOLVER_INPUTREADER_H


#include <vector>
#include <string>
#include <fstream>
#include "PuzzlePiece.h"

using namespace std;

class InputReader {
private:
    ofstream *outFile;

    bool checkMissingPieces(const vector<PuzzlePiece> &pieces, int size) throw(int);

    bool checkExtraIDs(const vector<PuzzlePiece> &pieces, int size) throw(int);

    void validatePieces(const vector<PuzzlePiece> &pieces, int size) throw(int);
public:
    bool valid = true;

    explicit InputReader(ofstream *output);

    void readInput(string path, vector<PuzzlePiece> &pieces) throw(int);
};


#endif //PUZZLESOLVER_INPUTREADER_H
