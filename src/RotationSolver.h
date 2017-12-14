//
// Created by dell on 12/12/2017.
//

#ifndef PUZZLESOLVER_ROTATIONSOLVER_H
#define PUZZLESOLVER_ROTATIONSOLVER_H

#include <vector>
#include "TypesMap.h"
#include "PuzzlePiece.h"
#include "RotationSolution.h"

using namespace std;

class RotationSolver {
private:
	Puzzle *_puzzle;
	RotationSolution _sol;
	bool _rotate = false;
	set<int> _rowLengths;

	TypesMap::Constraints getConstraints(int row, int col);

	bool fillFrames(int rowSize, int colSize, int corner, int col, int row, TypesMap &typesMap);
public:
	RotationSolver() = default;

	RotationSolver(Puzzle *puzzle, bool _rotate);

	bool solve();

	RotationSolution getSol();
};


#endif //PUZZLESOLVER_ROTATIONSOLVER_H
