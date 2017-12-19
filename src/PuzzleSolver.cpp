//
// Created by Tomer Amir on 21/11/2017.
//

#include "PuzzleSolver.h"
#include "PuzzleValidator.h"

PuzzleSolver::PuzzleSolver(Puzzle *puzzle, ofstream *output, bool rotation) :
        _rotate(rotation), _puzzle(puzzle), out(output), _types(_puzzle, _rotate)
{
    int size = static_cast<int>(puzzle->getPieces().size());

    for (int i = 1; i <= size; i++) {
        if (size % i == 0) {
            _rowLengths.insert(i);
        }
    }

    checkInput();
}

bool PuzzleSolver::checkEdges()
{
    int l = 0, t = 0, r = 0, b = 0;

	const auto &pieces = _puzzle->getPieces();

    for (auto p: pieces) {
        if (p.left() == 0) {
            l++;
        }

        if (p.top() == 0) {
            t++;
        }

        if (p.right() == 0) {
            r++;
        }

        if (p.bottom() == 0) {
            b++;
        }

    }

    auto newRows = _rowLengths;

    for (int rows: _rowLengths) {
		int cols = pieces.size() / rows;

		if (!_rotate) {
			if (l < cols || r < cols || t < rows || b < rows) {
				newRows.erase(rows);
			}
		} else {
			// TODO
		}
    }

    _rowLengths = newRows;

    return !newRows.empty();
}

bool PuzzleSolver::sumPieces()
{
    int v = 0;
    int h = 0;

    for (const auto &p: _puzzle->getPieces()) {
        v += p.top() + p.bottom();
        h += p.left() + p.right();
    }

	if (!_rotate) {
		return (v == 0) && (h == 0);
	}

	return (v + h) == 0;
}


void PuzzleSolver::checkInput()
{
    const vector<PuzzlePiece> &pieces = _puzzle->getPieces();

    if (!checkEdges()) {
        *(out) << "Cannot solve puzzle: wrong number of straight edges" << endl;
        _valid = false;
    }

    if (pieces.size() > 1) {
        checkCorners();
    }

    if (!sumPieces()) {
        *(out) << "Cannot solve puzzle: sum of edges is not zero" << endl;
        _valid = false;
    }
}

bool checkRow(Puzzle &puzzle)
{
    bool L = false, R = false;

    for (PuzzlePiece p: puzzle.getPieces()) {
        if (p.top() != 0 || p.bottom() != 0) {
            return false;
        }

        if (p.left() == 0) {
            L = true;
        }
        if (p.right() == 0) {
            R = true;
        }
    }

    return L && R;
}

bool checkCol(Puzzle &puzzle)
{
    bool T = false, B = false;

    for (PuzzlePiece p: puzzle.getPieces()) {
        if (p.left() != 0 || p.right() != 0) {
            return false;
        }

        if (p.top() == 0) {
            T = true;
        }
        if (p.bottom() == 0) {
            B = true;
        }
    }

    return T && B;
}


bool PuzzleSolver::checkRowCol()
{
    return checkRow(*_puzzle) || checkCol(*_puzzle);
}

void PuzzleSolver::checkCorners()
{
    int TL = 0, TR = 0, BL = 0, BR = 0;

    for (PuzzlePiece piece: _puzzle->getPieces()) {
        if (piece.top() == 0 && piece.left() == 0) {
            TL++;
        }
        if (piece.top() == 0 && piece.right() == 0) {
            TR++;
        }
        if (piece.bottom() == 0 && piece.left() == 0) {
            BL++;
        }
        if (piece.bottom() == 0 && piece.right() == 0) {
            BR++;
        }
    }

    if (!_rotate && !(TL && TR && BL && BR)) {
        if (!checkRowCol()) {
            if (TL == 0) {
                *(out) << "Cannot solve puzzle: missing corner element: TL" << endl;
                _valid = false;
            }
            if (TR == 0) {
                *(out) << "Cannot solve puzzle: missing corner element: TR" << endl;
                _valid = false;
            }
            if (BL == 0) {
                *(out) << "Cannot solve puzzle: missing corner element: BL" << endl;
                _valid = false;
            }
            if (BR == 0) {
                *(out) << "Cannot solve puzzle: missing corner element: BR" << endl;
                _valid = false;
            }
        }
    } else if (_rotate) {
		// TODO
	}
}


bool PuzzleSolver::solve() {
    return solve(PuzzleSolution());
}


bool PuzzleSolver::solve(PuzzleSolution sol) {
    if (_types.empty()) {
        if (PuzzleValidator::validate(*_puzzle, sol)) {
            _sol = sol;

            return true;
        } else {
            return false;
        }
    }

    auto goodTypes = getGoodTypes(sol, _types);

    for (const auto &type: goodTypes) {
        PuzzleSolution newSol = sol;

		auto piece = _types.getPiece(type);

		if (piece == nullptr) {
			continue;
		}

        newSol.addElement(piece->id);

        if (solve(newSol)) {
            return true;
        } else {
			_types.addPiece(piece);
		}
    }

    auto currRow = sol.getSolution().size() - 1;
    auto currRowSize = sol.getSolution().at(currRow).size();

    if (currRow != 0 && (sol.getSolution().at(currRow - 1).size() != currRowSize)) {
        return false;
    }

    auto search = _rowLengths.find(currRowSize);

    if (search != _rowLengths.end()) {
        PuzzleSolution newRowSol = sol;
        newRowSol.addRow();

        if (!sumEdges(sol.getSolution().back())) {
            return false;
        }

        if (solve(newRowSol)) {
            return true;
        }
    }

    return false;
}


const PuzzleSolution &PuzzleSolver::getSol() const {
    return _sol;
}


vector<TypesMap::Constraints> PuzzleSolver::getGoodTypes(PuzzleSolution sol, TypesMap types)
{
	vector<TypesMap::Constraints> res;
    auto matrix = sol.getSolution();
    auto size = matrix.size();

    if (matrix.size() > 1) {
        if (matrix.at(size - 1).size() == matrix.at(size - 2).size()) {
            return res;
        }

        auto rowSize = static_cast<int>(matrix.at(0).size());
        auto bottomSize = types.countBottomEdges();

        if (rowSize > bottomSize && bottomSize < types.size()) {
            return res;
        }
    }

    int sides[] = {-1, 0, 1};

    for (int l: sides) {
        for (int t: sides) {

            if (checkNewPiece(sol.getSolution(), TypesMap::Constraints(l, t, 0, 0))) {
                for (int r: sides) {
                    for (int b: sides) {

                        auto typePiece = TypesMap::Constraints(l, t, r, b);

                        auto tmp = types.getTypes(typePiece);
                        res.insert(res.end(), tmp.begin(), tmp.end());
                    }
                }
            }
        }
    }

    return res;
}


bool PuzzleSolver::checkNewPiece(const vector<vector<unsigned int>> &sol, const PuzzlePiece &piece) {
    auto row = sol.size() - 1;
    auto col = sol.at(row).size();

    // Top
    if (row > 0) {
        auto &top = _puzzle->getPieceById(sol.at(row - 1).at(col));

        if (top.bottom() + piece.top() != 0) {
            return false;
        }
    } else {
        if (piece.top() != 0) {
            return false;
        }
    }

    // Left
    if (col > 0) {
        auto &left = _puzzle->getPieceById(sol.at(row).at(col - 1));

        if (left.right() + piece.left() != 0) {
            return false;
        }
    } else {
        if (piece.left() != 0) {
            return false;
        }
    }

    return true;
}

bool PuzzleSolver::sumEdges(const vector<unsigned int> &lastRow) {
    int hor = 0;
    int ver = 0;

	_types.sumPieces(hor, ver);

    for (auto i: lastRow) {
        ver += _puzzle->getPieces().at(i - 1).bottom();
    }

	if (!_rotate) {
		return (hor == 0 && ver == 0);
	}

	return (hor + ver) == 0;
}
