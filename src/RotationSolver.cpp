//
// Created by tomer on 13-Dec-17.
//

#include "RotationSolver.h"

TypesMap::Constraints RotationSolver::getConstraints(int row, int col) const
{
	TypesMap::Constraints c;

	// LEFT
	if (col == 0) {
		c.left(0);
	} else {
		c.left(-_sol[row][col - 1]->right());
	}

	// TOP
	if (row == 0) {
		c.top(0);
	} else {
		c.top(-_sol[row - 1][col]->bottom());
	}

	// RIGHT
	if (col == _sol.get_width() - 1) {
		c.right(0);
	} else {
		c.right(-_sol[row][col + 1]->left());
	}

	// BOTTOM
	if (row == _sol.get_height() - 1) {
		c.bottom(0);
	} else {
		c.bottom(-_sol[row + 1][col]->top());
	}

	return c;
}

bool RotationSolver::fillFrames(int rowSize, int colSize, int index, int x, int y, TypesMap &typesMap) {
	auto constraints = getConstraints(x, y);
	auto goodTypes = typesMap.getTypes(constraints);

	for (auto &type: goodTypes) {
		auto piece = typesMap.getPiece(type);

		if (piece == nullptr) {
			continue;
		}

		_sol[x][y] = piece;

		// TODO: Export to another function
		int newX = -1, newY = -y;

		if (x == index) {
			if (x < index + colSize) {
				newX = x;
				newY = y + 1;
			} else {
				newX = x + 1;
				newY = y;
			}
		} else if (y == index + colSize - 1) {
			if (x > index + rowSize - 1) {
				newX = x + 1;
				newY = y;
			} else {
				newX = x;
				newY = y - 1;
			}
		} else if (x == index + rowSize - 1) {
			if (y > index) {
				newX = x;
				newY = y - 1;
			} else {
				newX = x - 1;
				newY = y;
			}
		} else {
			if (x > index) {
				newX = x - 1;
				newY = y;
			}
		}

		if (newX < 0) {
			int newIndex = index + 1;
			if (fillFrames(rowSize, colSize, newIndex, newIndex, newIndex, typesMap)) {
				return true;
			}
		} else if (fillFrames(rowSize, colSize, index, newX, newY, typesMap)) {
			return true;
		}

		_sol[x][y] = nullptr;
	}

	return false;
}

RotationSolver::RotationSolver(Puzzle *puzzle, bool _rotate) : _puzzle(puzzle), _rotate(_rotate)
{
	int size = _puzzle->size();

	for (int i = 1; i <= size; i++) {
		if (size % i == 0) {
			_rowLengths.insert(i);
		}
	}

	// TODO: Basic input checks
}

bool RotationSolver::solve() {
	TypesMap typesMap(_puzzle, _rotate);

	for (auto length: _rowLengths) {
		auto height = _puzzle->size() / length;
		_sol = RotationSolution(height, length);

		if (fillFrames(length, height, 0, 0, 0, typesMap)) {
			return true;
		}
	}

	// TODO: validate

	return false;
}

RotationSolution RotationSolver::getSol() {
	return _sol;
}


