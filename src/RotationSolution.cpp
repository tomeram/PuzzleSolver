//
// Created by tomer on 13-Dec-17.
//

#include "RotationSolution.h"

vector<PuzzlePiece *> RotationSolution::operator[](int row) {
	return matrix[row];
}
