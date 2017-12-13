//
// Created by tomer on 13-Dec-17.
//

#ifndef PUZZLESOLVER_ROTATIONSOLUTION_H
#define PUZZLESOLVER_ROTATIONSOLUTION_H

#include <vector>
#include <fstream>
#include "PuzzlePiece.h"

using namespace std;

class RotationSolution {
private:
	int _height, _width;
	vector<vector<PuzzlePiece*>> _matrix;

public:
	RotationSolution();

	RotationSolution(int height, int width);

	vector<PuzzlePiece*> operator[](int row) const;

	int get_height() const;

	int get_width() const;

	void print(ofstream *pOfstream);
};


#endif //PUZZLESOLVER_ROTATIONSOLUTION_H
