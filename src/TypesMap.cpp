//
// Created by Tomer Amir on 12/12/2017.
//

#include <set>
#include "TypesMap.h"

TypesMap::TypesMap(Puzzle *puzzle, bool rotate) : _puzzle(puzzle), _rotate(rotate)
{
    for (PuzzlePiece &p: _puzzle->getPieces()) {
        addPiece(&p);
    }
}

vector<int> &TypesMap::operator[](string type)
{
    return _types[type];
}

vector<TypesMap::Constraints> TypesMap::getTypes(Constraints c) const
{
    vector<TypesMap::Constraints> res;

	int rotations = _rotate ? 4 : 1;

	for (int i = 0; i < rotations; i++) {
		c.rotate(i);
		if (_types.find(c.getType()) != _types.end()) {
			auto copy = c;
			res.push_back(copy);
		}
	}

    return res;
}

PuzzlePiece *TypesMap::getPiece(Constraints type)
{
    int rotations = _rotate ? 4 : 1;

    for (int i = 0; i < rotations; i++) {
        type.rotate(i);
        auto strType = type.getType();


        if (_types.find(strType) == _types.end()) {
            continue;
        }

        vector<int> &pieces = _types[strType];
        type.rotate(0);

        int id = pieces.at(0);
        pieces.erase(pieces.begin());

        if (pieces.empty()) {
            _types.erase(strType);
        }

        auto piece = &_puzzle->getPieceById(id);

		for (int j = 0; j < rotations; j++) {
			piece->rotate(j);

			if (piece->getType() == type.getType())
				return piece;
		}
    }

    return nullptr;
}

TypesMap::Constraints::Constraints() : PuzzlePiece(-2, -2, -2, -2, -2) {}

TypesMap::Constraints::Constraints(int l, int t, int r, int b) : PuzzlePiece(-2, l, t, r, b) {}

bool operator<(const TypesMap::Constraints &left, const TypesMap::Constraints &right) {
    return left.getType() < right.getType();
}

void TypesMap::addPiece(PuzzlePiece *piece) {
	bool found = false;
	int rotations = 1;

	if (_rotate) {
		rotations = 4;
	}

	for (int i = 0; i < rotations; i++) {
		piece->rotate(i);

		auto type = piece->getType();

		if (_types.find(type) != _types.end()) {
			_types[type].push_back(piece->id);
			found = true;
			break;
		}
	}

	if (!found) {
		piece->rotate(0);
		_types[piece->getType()] = {piece->id};
	}
}

int TypesMap::size() {
	return _types.size();
}

bool TypesMap::empty() {
	return _types.empty();
}

int TypesMap::countBottomEdges() {
	int res = 0;

	for (const auto &type: _types) {
		if (_rotate) {
			if (type.first.find("0") != string::npos) {
				res += type.second.size();
			}
		} else if (type.first.back() == '0') {
			res += type.second.size();
		}
	}

	return res;
}

void TypesMap::sumPieces(int &hor, int &ver) {
	for (const auto &type: _types) {
		auto piece = _puzzle->getPieceById(type.second.at(0));
		hor += (piece.left() + piece.right()) * type.second.size();
		ver += (piece.top() + piece.bottom()) * type.second.size();
	}
}
