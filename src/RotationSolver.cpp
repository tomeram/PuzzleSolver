//
// Created by tomer on 13-Dec-17.
//

#include "RotationSolver.h"

TypesMap::Constraints RotationSolver::getConstraints(int row, int col)
{
	TypesMap::Constraints c;

	PuzzlePiece *neighbour;

	// LEFT
	if (col == 0) {
		c.left(0);
	} else {
		neighbour = _sol[row][col - 1];

		if (neighbour != nullptr) {
			c.left(-neighbour->right());
		} else {
			c.left(-2);
		}
	}

	// TOP
	if (row == 0) {
		c.top(0);
	} else {
		neighbour = _sol[row - 1][col];

		if (neighbour != nullptr) {
			c.top(-neighbour->bottom());
		} else {
			c.top(-2);
		}
	}

	// RIGHT
	if (col == _sol.get_width() - 1) {
		c.right(0);
	} else {
		neighbour = _sol[row][col + 1];

		if (neighbour != nullptr) {
			c.right(-neighbour->left());
		} else {
			c.right(-2);
		}
	}

	// BOTTOM
	if (row == _sol.get_height() - 1) {
		c.bottom(0);
	} else {
		neighbour = _sol[row + 1][col];

		if (neighbour != nullptr) {
			c.bottom(-neighbour->top());
		} else {
			c.bottom(-2);
		}
	}

	return c;
}

bool RotationSolver::fillFrames(int rowSize, int colSize, int corner, int col, int row, TypesMap &typesMap) {
	auto constraints = getConstraints(row, col);
	auto goodTypes = typesMap.getTypes(constraints);

	for (auto &type: goodTypes) {
		auto piece = typesMap.getPiece(type);

		if (piece == nullptr) {
			continue;
		}

		_sol[col][row] = piece;

		// TODO: Export to another function
		int newCol = -1, newRow = -1;

		int lastRow = corner + colSize - 1;
		int lastCol = corner + rowSize - 1;

		if (row == corner) {
			if (col < lastCol) {
				newCol = col + 1;
				newRow = row;
			} else {
				newCol = col;
				newRow = row + 1;
			}
		} else if (col == lastCol) {
			if (row < lastRow) {
				newCol = col;
				newRow = row + 1;
			} else {
				newCol = col - 1;
				newRow = row;
			}
		} else if (col == lastRow) {
			if (col > corner) {
				newCol = col - 1;
				newRow = row;
			} else {
				newCol = col;
				newRow = row - 1;
			}
		} else {
			if (row > corner) {
				newCol = col;
				newRow = row - 1;
			}
		}

		if (newCol < 0) {
			int newIndex = corner + 1;

			auto min = std::min(_sol.get_height(), _sol.get_width());

			min = (min / 2) + (min % 2);

			if (corner < min) {
				if (fillFrames(rowSize, colSize, newIndex, newIndex, newIndex, typesMap)) {
					return true;
				}
			}
		} else if (fillFrames(rowSize, colSize, corner, newCol, newRow, typesMap)) {
			return true;
		}

		typesMap.addPiece(piece);
		_sol[col][row] = nullptr;
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
		_sol.resize(height, length);

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


