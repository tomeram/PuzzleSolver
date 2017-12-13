//
// Created by tomer on 13-Dec-17.
//

#include "RotationSolution.h"

vector<PuzzlePiece *> RotationSolution::operator[](int row) {
	return _matrix[row];
}

RotationSolution::RotationSolution(int height, int width) : _height(height), _width(width)
{
	_matrix = vector<vector<PuzzlePiece*>>(_height, vector<PuzzlePiece*>(_width));
}
