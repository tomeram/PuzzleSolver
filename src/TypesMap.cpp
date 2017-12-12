//
// Created by Tomer Amir on 12/12/2017.
//

#include "TypesMap.h"

TypesMap::TypesMap(Puzzle *puzzle, bool rotate) : _puzzle(puzzle), _rotate(rotate) {
    for (PuzzlePiece p: _puzzle->getPieces()) {
        bool found = false;
        int rotations = 1;

        if (_rotate) {
            rotations = 4;
        }

        for (int i = 0; i < rotations; i++) {
            p.rotate(i);

            auto type = p.getType();

            if (_types.find(type) != _types.end()) {
                _types[type].push_back(p.id);
                found = true;
                break;
            }
        }

        if (!found) {
            p.rotate(0);
            _types[p.getType()] = {p.id};
        }
    }
}

vector<int> &TypesMap::operator[](string type) {
    return _types[type];
}

void TypesMap::erase(const string &type) {
    _types.erase(type);
}

bool TypesMap::find(string type) {
    return _types.find(type) != _types.end();

}
