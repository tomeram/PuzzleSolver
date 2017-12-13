//
// Created by tomer on 13-Dec-17.
//

#ifndef PUZZLESOLVER_ROTATIONSOLUTION_H
#define PUZZLESOLVER_ROTATIONSOLUTION_H

#include <vector>
#include "PuzzlePiece.h"

using std::vector;

class RotationSolution {
private:
	int _height, _width;
	vector<vector<PuzzlePiece*>> _matrix;

public:
	RotationSolution(int height, int width);

	vector<PuzzlePiece*> operator[](int row);
};


#endif //PUZZLESOLVER_ROTATIONSOLUTION_H
