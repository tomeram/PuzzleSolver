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
public:
    class Constraints : PuzzlePiece {
    private:
        friend class TypesMap;
    public:
        Constraints();
        Constraints(int l, int t, int r, int b);
    };

private:
    map<string, vector<int>> _types;
    Puzzle *_puzzle;
    bool _rotate;

    set<string> checkBottom(Constraints &c, Constraints &p) const;
    set<string> checkRight(Constraints &c, Constraints &p) const;
    set<string> checkTop(Constraints &c, Constraints &p) const;
    set<string> checkLeft(Constraints &c, Constraints &p) const;

public:
    explicit TypesMap(Puzzle *puzzle, bool rotate = false);

    vector<int> &operator[](string type);

    void erase(const string &basic_string);

    bool find(string basic_string);

    vector<string> getTypes(Constraints c) const;

    PuzzlePiece* getPiece(string type);
};


#endif //PUZZLESOLVER_TYPESMAP_H
