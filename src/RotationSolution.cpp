//
// Created by tomer on 13-Dec-17.
//

#include "RotationSolution.h"

vector<PuzzlePiece*> RotationSolution::operator[](int row) const {
	return _matrix[row];
}

RotationSolution::RotationSolution() : RotationSolution(0, 0) {}

RotationSolution::RotationSolution(int height, int width) : _height(height), _width(width)
{
	_matrix = vector<vector<PuzzlePiece*>>(_height, vector<PuzzlePiece*>(_width));
}

int RotationSolution::get_height() const {
	return _height;
}

int RotationSolution::get_width() const {
	return _width;
}

void RotationSolution::print(ofstream *out) {
	for (auto row: _matrix) {
		for (unsigned int i = 0; i < row.size(); i++) {
			*(out) << row.at(i);

			if (i < row.size() - 1) {
				*(out) << " ";
			}
		}

		*(out) << endl;
	}
}
