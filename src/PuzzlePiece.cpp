//
// Created by Tomer Amir on 07/11/2017.
//

#include "PuzzlePiece.h"

#include <iostream>

using namespace std;

PuzzlePiece::PuzzlePiece(int id, int l, int t, int r, int b) : id(id), l(l), t(t), r(r), b(b)
{}

PuzzlePiece::~PuzzlePiece() = default;

void PuzzlePiece::print() const
{
    cout << id << " " << l << " " << t << " " << r << " " << b << endl;
}
