//
// Created by Kobi Hazan on 12/12/2017.
//

#include "RotationSolver.h"

//RotationSolver::sol()
//int m = colSize, n = rowSize;
//
//for(int i = 0 ; i < m ; ++i) {
//    //Grow Columns by n
//    sol[i].resize(n);
//}

RotationSolver::RotationSolver() = default;

int RotationSolver::getPair(int p) {
	return -p;
}

bool RotationSolver::fillRow(int rowSize, int colSize, int row, int col_left, RotationSolution sol, TypesMap &typesMap) {
	if (col_left > col_left + rowSize) {
		return true;
	}

	TypesMap::Constraints c;

	if (col_left-1 > 0) {
		PuzzlePiece* myLeft = sol[col_left-1][row];
		if (myLeft == nullptr) {
			c.left(-2);
		} else {
			c.left(getPair(myLeft->left()));
		}

	} else {
		c.left(0);
	}

	if (row-1 > 0) {
		PuzzlePiece* myTop = sol[col_left][row-1];
		if (myTop == nullptr) {
			c.top(-2);
		} else {
			c.top(getPair(myTop->top()));
		}
	} else {
		c.top(0);
	}

	if (row+1 < rowSize) {
		PuzzlePiece* myBottom = sol[col_left][row+1];
		if (myBottom == nullptr) {
			c.bottom(-2);
		} else {
			c.bottom(getPair(myBottom->bottom()));
		}
	} else {
		c.bottom(0);
	}

	if (col_left+1 < colSize) {
		PuzzlePiece* myright = sol[col_left+1][row];
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
			sol[col_left][row]= piece;

			if (fillRow(rowSize, colSize, row, col_left + 1, sol, newMap)) {
				return true;
			}
			else{
				sol[col_left][row] = nullptr;
			}
		}
	}

	return false;
}


bool RotationSolver::topRow(int rowSize, int colSize, int row_top, int col_left, RotationSolution sol, TypesMap &typesMap) {
	return fillRow(rowSize, colSize, row_top, col_left, sol, typesMap);
}

bool RotationSolver::bottomRow(int rowSize, int colSize, int row_bott, int col_left, RotationSolution sol, TypesMap &typesMap) {
	return fillRow(rowSize, colSize, row_bott, col_left, sol, typesMap);
}

bool RotationSolver::fillCol(int rowSize, int colSize, int col, int row_top, int row_bott, RotationSolution sol, TypesMap &typesMap) {
	if (row_top > row_bott) {
		return true;
	}
	else{
		TypesMap::Constraints c;
		if (col-1 > 0) {
			PuzzlePiece* myLeft = sol[col-1][row_top];
			if (myLeft == nullptr) {
				c.left(-2);
			} else {
				c.left(getPair(myLeft->left()));
			}

		} else {
			c.left(0);
		}

		if (col+1 < colSize) {
			PuzzlePiece* myTop = sol[col+1][row_top];
			if (myTop == nullptr) {
				c.top(-2);
			} else {
				c.top(getPair(myTop->top()));
			}
		} else {
			c.top(0);
		}

		if (row_top+1 < rowSize) {
			PuzzlePiece* myBottom = sol[col][row_top+1];
			if (myBottom == nullptr) {
				c.bottom(-2);
			} else {
				c.bottom(getPair(myBottom->bottom()));
			}
		} else {
			c.bottom(0);
		}

		if (row_top-1 > 0) {
			PuzzlePiece* myright = sol[col][row_top-1];
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
					sol[col][row_top]= piece;
					bool b= fillCol(rowSize, colSize, col, row_top+1, row_bott, sol, newMap);
					if (b) {
						return true;
					}
					else{
						sol[col][row_top]= nullptr;
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

bool RotationSolver::leftCol(int rowSize, int colSize, int col_left, int row_top, int row_bott, RotationSolution sol, TypesMap &typesMap) {
	return fillCol(rowSize, colSize, col_left, row_top, row_bott, sol, typesMap);
}

bool RotationSolver::rightCol(int rowSize, int colSize, int col_right, int row_top, int row_bott,
							  RotationSolution sol, TypesMap &typesMap) {
	return fillCol(rowSize, colSize, col_right, row_top, row_bott, sol, typesMap);
}

bool RotationSolver::fillFrames(int rowSize, int colSize, int row_top, int row_bott,
								int col_left, int col_right, RotationSolution sol, TypesMap &typesMap) {

	if (col_left > col_right && row_top > row_bott) {
		return true;
	}

	if (col_left < col_right && row_top < row_bott) {
		if (topRow(rowSize, colSize, row_top, col_left, sol, typesMap) &&
			bottomRow(rowSize, colSize, row_bott, col_left, sol, typesMap) &&
			rightCol(rowSize, colSize, col_right, row_top, row_bott, sol, typesMap) &&
			leftCol(rowSize, colSize, col_left, row_top, row_bott, sol, typesMap))
		{
			fillFrames(rowSize, colSize, row_top + 1, row_bott - 1, col_left +1, col_right -1, sol, typesMap);
		} else {
			return false;
		}
	}

	if (col_left == col_right && row_top < row_bott) {
		if (topRow(rowSize, colSize, row_top, col_left, sol, typesMap) &&
			bottomRow(rowSize, colSize, row_bott, col_left, sol, typesMap) &&
			leftCol(rowSize, colSize, col_left, row_top, row_bott, sol, typesMap))
		{
			fillFrames(rowSize, colSize, row_top + 1, row_bott - 1, col_left +1, col_right, sol, typesMap);
		} else {
			return false;
		}
	}
	if (col_left < col_right && row_top == row_bott) {
		if (leftCol(rowSize, colSize, col_left, row_top, row_bott, sol, typesMap) &&
			rightCol(rowSize, colSize, col_right, row_top, row_bott, sol, typesMap) &&
			topRow(rowSize, colSize, row_top, col_left, sol, typesMap))
		{
			fillFrames(rowSize, colSize, row_top + 1, row_bott, col_left +1, col_right -1, sol, typesMap);
		} else {
			return false;
		}
	}
	if (col_left == col_right && row_top == row_bott) {
		if (topRow(rowSize, colSize, row_top, col_left, sol, typesMap) &&
			leftCol(rowSize, colSize, col_left, row_top, row_bott, sol, typesMap))
		{
			fillFrames(rowSize, colSize, row_top + 1, row_bott, col_left +1, col_right, sol, typesMap);
		} else {
			return false;
		}
	}
	if (col_left < col_right && row_top > row_bott) {
		if (leftCol(rowSize, colSize, col_left, row_top, row_bott, sol, typesMap) &&
			rightCol(rowSize, colSize, col_right, row_top, row_bott, sol, typesMap))
		{
			fillFrames(rowSize, colSize, row_top, row_bott, col_left +1, col_right -1, sol, typesMap);
		} else {
			return false;
		}
	}
	if (col_left > col_right && row_top < row_bott) {
		if (topRow(rowSize, colSize, row_top, col_left, sol, typesMap) &&
			bottomRow(rowSize, colSize, row_bott, col_left, sol, typesMap))
		{
			fillFrames(rowSize, colSize, row_top+1, row_bott-1, col_left, col_right, sol, typesMap);
		} else {
			return false;
		}
	}
	return false;
}


