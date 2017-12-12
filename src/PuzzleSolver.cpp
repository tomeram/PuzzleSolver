//
// Created by Tomer Amir on 21/11/2017.
//

#include "PuzzleSolver.h"
#include "PuzzleValidator.h"

PuzzleSolver::PuzzleSolver(const Puzzle &puzzle, ofstream *output, bool rotation) :
        rotate(rotation), puzzle(puzzle), out(output)
{
    int size = static_cast<int>(puzzle.getPieces().size());

    for (int i = 1; i <= size; i++) {
        if (size % i == 0) {
            rowLengths.insert(i);
        }
    }

    for (PuzzlePiece p: puzzle.getPieces()) {
        bool found = false;
        int rotations = 1;

        if (rotate || true) {
            rotations = 4;
        }

        for (int i = 0; i < rotations; i++) {
            p.rotate(i);

            auto type = p.getType();

            if (types.find(type) != types.end()) {
                types[type].push_back(p.id);
                found = true;
                break;
            }
        }

        if (!found) {
            p.rotate(0);
            types[p.getType()] = {p.id};
        }
    }

    checkInput();
}


bool checkEdges(const vector<PuzzlePiece> &pieces, set<int> &rowLengths)
{
    int l = 0, t = 0, r = 0, b = 0;
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

    auto newRows = rowLengths;

    for (int rows: rowLengths) {
        int cols = pieces.size() / rows;

        if (l < cols || r < cols || t < rows || b < rows) {
            newRows.erase(rows);
        }
    }

    rowLengths = newRows;

    return !newRows.empty();
}


bool sumPieces(const vector<PuzzlePiece> &pieces)
{
    int v = 0;
    int h = 0;

    for (PuzzlePiece p: pieces) {
        v += p.top() + p.bottom();
        h += p.left() + p.right();
    }

    return (v == 0) && (h == 0);
}


void PuzzleSolver::checkInput()
{
    const vector<PuzzlePiece> &pieces = puzzle.getPieces();

    if (!checkEdges(pieces, rowLengths)) {
        *(out) << "Cannot solve puzzle: wrong number of straight edges" << endl;
        valid = false;
    }

    if (pieces.size() > 1) {
        checkCorners();
    }

    if (!sumPieces(pieces)) {
        *(out) << "Cannot solve puzzle: sum of edges is not zero" << endl;
        valid = false;
    }
}



bool checkRow(const Puzzle &puzzle)
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


bool checkCol(const Puzzle &puzzle)
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
    return checkRow(puzzle) || checkCol(puzzle);
}


void PuzzleSolver::checkCorners()
{
    int TL = 0, TR = 0, BL = 0, BR = 0;

    for (PuzzlePiece piece: puzzle.getPieces()) {
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

    if (!(TL && TR && BL && BR)) {
        if (!checkRowCol()) {
            if (TL == 0) {
                *(out) << "Cannot solve puzzle: missing corner element: TL" << endl;
                valid = false;
            }
            if (TR == 0) {
                *(out) << "Cannot solve puzzle: missing corner element: TR" << endl;
                valid = false;
            }
            if (BL == 0) {
                *(out) << "Cannot solve puzzle: missing corner element: BL" << endl;
                valid = false;
            }
            if (BR == 0) {
                *(out) << "Cannot solve puzzle: missing corner element: BR" << endl;
                valid = false;
            }
        }
    }
}


bool PuzzleSolver::solve() {
    return this->solve(PuzzleSolution(), this->puzzle.getPieces(), getEdges(), types);
}


bool PuzzleSolver::solve(PuzzleSolution sol, vector<PuzzlePiece> unused, Edges edges, map<string, vector<int>> types) {
    if (unused.empty()) {
        if (PuzzleValidator::validate(puzzle, sol)) {
            this->sol = sol;

            return true;
        } else {
            return false;
        }
    }

    vector<string> goodTypes = addNextElement(sol, unused, edges, types);

    for (const string &type: goodTypes) {
        vector<PuzzlePiece> newUnused = unused;
        PuzzleSolution newSol = sol;
        Edges newEdges = edges;
        map<string, vector<int>> newTypes = types;

        vector<int> &usedType = newTypes[type];

        int id = usedType.at(0);
        usedType.erase(usedType.begin());

        if (usedType.empty()) {
            newTypes.erase(type);
        }

        newEdges.removePiece(id);
        newSol.addElement(static_cast<unsigned int>(id));

        for (unsigned int i = 0; i < unused.size(); i++) {
            if (unused.at(i).id == id) {
                newUnused.erase(newUnused.begin() + i);
            }
        }

        if (this->solve(newSol, newUnused, newEdges, newTypes)) {
            return true;
        }
    }

    auto currRow = static_cast<int>(sol.getSolution().size()) - 1;
    unsigned int currRowSize = sol.getSolution().at(currRow).size();

    if (currRow != 0 && (sol.getSolution().at(currRow - 1).size() != currRowSize)) {
        return false;
    }

    auto search = rowLengths.find(currRowSize);

    if (search != rowLengths.end()) {
        PuzzleSolution newRowSol = sol;
        newRowSol.addRow();

        if (!sumEdges(sol.getSolution().back(), unused)) {
            return false;
        }

        if (this->solve(newRowSol, unused, edges, types)) {
            return true;
        }
    }

    return false;
}


const PuzzleSolution &PuzzleSolver::getSol() const {
    return sol;
}


vector<string> PuzzleSolver::addNextElement(PuzzleSolution sol, vector<PuzzlePiece> unused, Edges edges,
                                            map<string, vector<int>> types)
{
    vector<string> res;
    auto matrix = sol.getSolution();
    auto size = matrix.size();

    if (matrix.size() > 1) {
        if (matrix.at(size - 1).size() == matrix.at(size - 2).size()) {
            return res;
        }

        unsigned int rowSize = matrix.at(0).size();
        unsigned int bottomSize = edges.bottom.size();

        if (rowSize > bottomSize && bottomSize < unused.size()) {
            return res;
        }
    }

    int sides[] = {-1, 0, 1};

    for (int l: sides) {
        for (int t: sides) {

            if (checkNewPiece(sol.getSolution(), PuzzlePiece(0, l, t, 0, 0))) {
                for (int r: sides) {
                    for (int b: sides) {

                        auto typePiece = PuzzlePiece(-1, l, t, r, b);

                        string typeID = typePiece.getType();

                        if (types.find(typeID) != types.end()) {
                            res.push_back(typeID);
                        }
                    }
                }
            }
        }
    }

    return res;
}


bool PuzzleSolver::checkNewPiece(const vector<vector<unsigned int>> &sol, const PuzzlePiece &piece) {
    int row = sol.size() - 1;
    int col = sol.at(row).size();

    // Top
    if (row > 0) {
        auto &top = puzzle.getPieceById(sol.at(row - 1).at(col));

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
        auto &left = puzzle.getPieceById(sol.at(row).at(col - 1));

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


Edges PuzzleSolver::getEdges() {
    Edges res;

    for (PuzzlePiece piece: puzzle.getPieces()) {
        if (piece.left() == 0) {
            res.left.insert(piece.id);
        }

        if (piece.top() == 0) {
            res.top.insert(piece.id);
        }

        if (piece.right() == 0) {
            res.right.insert(piece.id);
        }

        if (piece.bottom() == 0) {
            res.bottom.insert(piece.id);
        }
    }

    return res;
}


bool PuzzleSolver::sumEdges(const vector<unsigned int> &lastRow, vector<PuzzlePiece> &pieces) {
    int hor = 0;
    int ver = 0;

    for (PuzzlePiece p: pieces) {
        hor += p.left() + p.right();
        ver += p.top() + p.bottom();
    }

    for (int i: lastRow) {
        ver += puzzle.getPieces().at(i - 1).bottom();
    }

    return (hor == 0 && ver == 0);
}


void Edges::removePiece(int id) {
    left.erase(id);
    top.erase(id);
    right.erase(id);
    bottom.erase(id);
}
