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
    explicit TypesMap(Puzzle *puzzle, bool rotate = false);

    vector<int> &operator[](string type);

    void erase(const string &basic_string);

    bool find(string basic_string);
};


#endif //PUZZLESOLVER_TYPESMAP_H
