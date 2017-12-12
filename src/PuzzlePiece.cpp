//
// Created by Tomer Amir on 07/11/2017.
//

#include "PuzzlePiece.h"

#include <iostream>

using namespace std;

PuzzlePiece::PuzzlePiece(int id, int l, int t, int r, int b) : id(id)
{
    sides[0] = l;
    sides[1] = t;
    sides[2] = r;
    sides[3] = b;
}

void PuzzlePiece::rotate(int rotation)
{
    this->rotation = rotation;
}

int PuzzlePiece::left() const
{
    return sides[rotation];
}

int PuzzlePiece::top() const
{
    return sides[(1 + rotation) % 4];
}

int PuzzlePiece::right() const
{
    return sides[(2 + rotation) % 4];
}

int PuzzlePiece::bottom() const
{
    return sides[(3 + rotation) % 4];
}

string PuzzlePiece::getRotation() const {
    if (rotation == 0) {
        return "";
    }

    if (rotation == 1) {
        return "90";
    }

    if (rotation == 2) {
        return "180";
    }

    return "270";
}

