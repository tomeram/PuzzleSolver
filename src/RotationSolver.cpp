//
// Created by Kobi Hazan on 12/12/2017.
//

#include "RotationSolver.h"

int RotationSolver::getPair(int p) {
	return -p;
}

bool RotationSolver::fillRow(int rowSize, int colSize, int row, int col, TypesMap &typesMap) {
	if (col > col + rowSize) {
		return true;
	}

	TypesMap::Constraints c;

	if (col-1 > 0) {
		PuzzlePiece* myLeft = _sol[col-1][row];
		if (myLeft == nullptr) {
			c.left(-2);
		} else {
			c.left(getPair(myLeft->left()));
		}

	} else {
		c.left(0);
	}

	if (row-1 > 0) {
		PuzzlePiece* myTop = _sol[col][row-1];
		if (myTop == nullptr) {
			c.top(-2);
		} else {
			c.top(getPair(myTop->top()));
		}
	} else {
		c.top(0);
	}

	if (row+1 < rowSize) {
		PuzzlePiece* myBottom = _sol[col][row+1];
		if (myBottom == nullptr) {
			c.bottom(-2);
		} else {
			c.bottom(getPair(myBottom->bottom()));
		}
	} else {
		c.bottom(0);
	}

	if (col+1 < colSize) {
		PuzzlePiece* myright = _sol[col+1][row];
		if (myright == nullptr) {
			c.right(-2);
		} else {
			c.right(getPair(myright->right()));
		}
	} else {
		c.right(0);
	}

	auto goodTypes =  typesMap.getTypes(c);

	for (const auto &type: goodTypes) {
		TypesMap newMap = typesMap;
		PuzzlePiece* piece = newMap.getPiece(type);

		if (piece != nullptr) {
			_sol[col][row]= piece;

			if (fillRow(rowSize, colSize, row, col + 1, newMap)) {
				return true;
			}
			else{
				_sol[col][row] = nullptr;
			}
		}
	}

	return false;
}


bool RotationSolver::topRow(int rowSize, int colSize, int row_top, int col, TypesMap &typesMap) {
	return fillRow(rowSize, colSize, row_top, col, typesMap);
}

bool RotationSolver::bottomRow(int rowSize, int colSize, int row_bott, int col, TypesMap &typesMap) {
	return fillRow(rowSize, colSize, row_bott, col, typesMap);
}

bool RotationSolver::fillCol(int rowSize, int colSize, int col, int row_top, int row_bott, TypesMap &typesMap) {
	if (row_top > row_bott) {
		return true;
	}
	else{
		TypesMap::Constraints c;
		if (col-1 > 0) {
			PuzzlePiece* myLeft = _sol[col-1][row_top];
			if (myLeft == nullptr) {
				c.left(-2);
			} else {
				c.left(getPair(myLeft->left()));
			}

		} else {
			c.left(0);
		}

		if (col+1 < colSize) {
			PuzzlePiece* myTop = _sol[col+1][row_top];
			if (myTop == nullptr) {
				c.top(-2);
			} else {
				c.top(getPair(myTop->top()));
			}
		} else {
			c.top(0);
		}

		if (row_top+1 < rowSize) {
			PuzzlePiece* myBottom = _sol[col][row_top+1];
			if (myBottom == nullptr) {
				c.bottom(-2);
			} else {
				c.bottom(getPair(myBottom->bottom()));
			}
		} else {
			c.bottom(0);
		}

		if (row_top-1 > 0) {
			PuzzlePiece* myright = _sol[col][row_top-1];
			if (myright == nullptr) {
				c.right(-2);
			} else {
				c.right(getPair(myright->right()));
			}
		} else {
			c.right(0);
		}

		auto list = typesMap.getTypes(c);
		if (! list.empty()) {
			for (const auto &type: list) {
				TypesMap newMap = typesMap;
				PuzzlePiece* piece = newMap.getPiece(type);
				if (piece != nullptr) {
					_sol[col][row_top]= piece;
					bool b= fillCol(rowSize, colSize, col, row_top+1, row_bott, newMap);
					if (b) {
						return true;
					}
					else{
						_sol[col][row_top]= nullptr;
					}
				}
			}
			return false;
		}
		else{
			return false;
		}
	}
}

bool RotationSolver::leftCol(int rowSize, int colSize, int col, int row_top, int row_bott, TypesMap &typesMap) {
	return fillCol(rowSize, colSize, col, row_top, row_bott, typesMap);
}

bool RotationSolver::rightCol(int rowSize, int colSize, int col_right, int row_top, int row_bott, TypesMap &typesMap) {
	return fillCol(rowSize, colSize, col_right, row_top, row_bott, typesMap);
}

bool RotationSolver::fillFrames(int rowSize, int colSize, int row_top, int row_bott,
								int col, int col_right, TypesMap &typesMap) {

	if (col > col_right && row_top > row_bott) {
		return true;
	}

	if (col < col_right && row_top < row_bott) {
		if (topRow(rowSize, colSize, row_top, col, typesMap) &&
			bottomRow(rowSize, colSize, row_bott, col, typesMap) &&
			rightCol(rowSize, colSize, col_right, row_top, row_bott, typesMap) &&
			leftCol(rowSize, colSize, col, row_top, row_bott, typesMap))
		{
			fillFrames(rowSize, colSize, row_top + 1, row_bott - 1, col +1, col_right -1, typesMap);
		} else {
			return false;
		}
	}

	if (col == col_right && row_top < row_bott) {
		if (topRow(rowSize, colSize, row_top, col, typesMap) &&
			bottomRow(rowSize, colSize, row_bott, col, typesMap) &&
			leftCol(rowSize, colSize, col, row_top, row_bott, typesMap))
		{
			fillFrames(rowSize, colSize, row_top + 1, row_bott - 1, col +1, col_right, typesMap);
		} else {
			return false;
		}
	}
	if (col < col_right && row_top == row_bott) {
		if (leftCol(rowSize, colSize, col, row_top, row_bott, typesMap) &&
			rightCol(rowSize, colSize, col_right, row_top, row_bott, typesMap) &&
			topRow(rowSize, colSize, row_top, col, typesMap))
		{
			fillFrames(rowSize, colSize, row_top + 1, row_bott, col +1, col_right -1, typesMap);
		} else {
			return false;
		}
	}
	if (col == col_right && row_top == row_bott) {
		if (topRow(rowSize, colSize, row_top, col, typesMap) &&
			leftCol(rowSize, colSize, col, row_top, row_bott, typesMap))
		{
			fillFrames(rowSize, colSize, row_top + 1, row_bott, col +1, col_right, typesMap);
		} else {
			return false;
		}
	}
	if (col < col_right && row_top > row_bott) {
		if (leftCol(rowSize, colSize, col, row_top, row_bott, typesMap) &&
			rightCol(rowSize, colSize, col_right, row_top, row_bott, typesMap))
		{
			fillFrames(rowSize, colSize, row_top, row_bott, col +1, col_right -1, typesMap);
		} else {
			return false;
		}
	}
	if (col > col_right && row_top < row_bott) {
		if (topRow(rowSize, colSize, row_top, col, typesMap) &&
			bottomRow(rowSize, colSize, row_bott, col, typesMap))
		{
			fillFrames(rowSize, colSize, row_top+1, row_bott-1, col, col_right, typesMap);
		} else {
			return false;
		}
	}
	return false;
}


