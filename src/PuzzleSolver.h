//
// Created by Tomer Amir on 21/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLESOLVER_H
#define PUZZLESOLVER_PUZZLESOLVER_H

#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

#include "Puzzle.h"
#include "PuzzleSolution.h"
#include "TypesMap.h"

using namespace std;

class PuzzleSolver {
private:
    bool _rotate = false;
    bool _valid = true;
    Puzzle *_puzzle;
    ofstream *out;
    PuzzleSolution _sol;
    set<int> _rowLengths;
    TypesMap _types;


    bool solve(PuzzleSolution sol);

    bool checkNewPiece(const vector<vector<unsigned int>> &sol, const PuzzlePiece &piece);

	vector<TypesMap::Constraints> getGoodTypes(PuzzleSolution sol, TypesMap types);

    bool checkRowCol();

    void checkCorners();

    void checkInput();

    bool sumEdges(const vector<unsigned int> &lastRow);

	bool checkEdges();

	bool sumPieces();

public:
    PuzzleSolver(Puzzle *puzzle, ofstream *output, bool rotation);

    bool isValid() {
        return _valid;
    }

    bool solve();

    const PuzzleSolution &getSol() const;
};


#endif //PUZZLESOLVER_PUZZLESOLVER_H
