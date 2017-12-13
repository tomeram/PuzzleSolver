//
// Created by Tomer Amir on 12/12/2017.
//

#include <set>
#include "TypesMap.h"

TypesMap::TypesMap(Puzzle *puzzle, bool rotate) : _puzzle(puzzle), _rotate(rotate)
{
    _rotate = true;
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

vector<int> &TypesMap::operator[](string type)
{
    return _types[type];
}

void TypesMap::erase(const string &type)
{
    _types.erase(type);
}

bool TypesMap::find(string type)
{
    return _types.find(type) != _types.end();

}

const auto SIDES = {-1, 0, 1};

set<string> TypesMap::checkBottom(Constraints &c, Constraints &p) const
{
    set<string> res;
    auto sides = SIDES;

    if (c.bottom() > -2) {
        sides = {c.bottom()};
    }

    for (auto side: sides) {
        p.bottom(side);

        int rotations = _rotate ? 4 : 1;

        for (int i = 0; i < rotations; i++) {
            p.rotate(i);
            if (_types.find(p.getType()) != _types.end()) {
                p.rotate(0);
                res.insert(p.getType());

                break;
            }
        }
    }

    return res;
}

set<string> TypesMap::checkRight(Constraints &c, Constraints &p) const
{
    set<string> res;
    set<string> tmp;

    auto sides = SIDES;

    if (c.right() > -2) {
        sides = {c.right()};
    }

    for (auto side: sides) {
        p.right(side);
        tmp = checkBottom(c, p);
        res.insert(tmp.begin(), tmp.end());
    }

    return res;
}

set<string> TypesMap::checkTop(Constraints &c, Constraints &p) const
{
    set<string> res;
    set<string> tmp;

    auto sides = SIDES;

    if (c.top() > -2) {
        sides = {c.top()};
    }

    for (auto side: sides) {
        p.top(side);
        tmp = checkRight(c, p);
        res.insert(tmp.begin(), tmp.end());
    }

    return res;
}

set<string> TypesMap::checkLeft(Constraints &c, Constraints &p) const
{
    set<string> res;
    set<string> tmp;

    auto sides = SIDES;

    if (c.left() > -2) {
        sides = {c.left()};
    }

    for (auto side: sides) {
        p.left(side);
        tmp = checkTop(c, p);
        res.insert(tmp.begin(), tmp.end());
    }

    return res;
}

vector<string> TypesMap::getTypes(Constraints c) const
{
    Constraints p;
    set<string> resSet = checkLeft(c, p);


    vector<string> res;
    res.insert(res.end(), resSet.begin(), resSet.end());

    return res;
}

PuzzlePiece *TypesMap::getPiece(string type)
{
    // TODO
    type = "5";
    return nullptr;
}

TypesMap::Constraints::Constraints() : PuzzlePiece(-2, -2, -2, -2, -2) {}
TypesMap::Constraints::Constraints(int l, int t, int r, int b) : PuzzlePiece(-2, l, t, r, b) {}
