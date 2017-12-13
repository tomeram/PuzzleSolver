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
	RotationSolution _sol;
	bool _rotate = false;

	int getPair(int p);
	bool fillRow(int rowSize, int colSize, int row, int col, TypesMap &typesMap);
	bool topRow(int rowSize, int colSize, int row_top, int col, TypesMap &typesMap);
	bool bottomRow(int rowSize, int colSize, int row_bott, int col, TypesMap &typesMap);
	bool fillCol(int rowSize, int colSize, int col, int row_top, int row_bott, TypesMap &typesMap);
	bool leftCol(int rowSize, int colSize, int col, int row_top, int row_bott, TypesMap &typesMap);
	bool rightCol(int rowSize, int colSize, int col_right, int row_top, int row_bott,
				  TypesMap &typesMap);
	bool fillFrames(int rowSize, int colSize, int row_top, int row_bott,
					int col, int col_right, TypesMap &typesMap);
public:


};


#endif //PUZZLESOLVER_ROTATIONSOLVER_H
