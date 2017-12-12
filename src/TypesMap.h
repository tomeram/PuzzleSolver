//
// Created by Tomer Amir on 12/12/2017.
//

#ifndef PUZZLESOLVER_TYPESMAP_H
#define PUZZLESOLVER_TYPESMAP_H

#include <map>
#include <string>
#include <vector>
#include "Puzzle.h"

using namespace std;

class TypesMap {
private:
    map<string, vector<int>> _types;
    Puzzle *_puzzle;
    bool _rotate;

public:
    struct Constraints {
        int l = -2, t = -2, r = -2, b = -2;
    };

    explicit TypesMap(Puzzle *puzzle, bool rotate = false);

    vector<int> &operator[](string type);

    void erase(const string &basic_string);

    bool find(string basic_string);

    vector<string> getTypes(Constraints c) const;

    PuzzlePiece* getPiece(string type);
};


#endif //PUZZLESOLVER_TYPESMAP_H
