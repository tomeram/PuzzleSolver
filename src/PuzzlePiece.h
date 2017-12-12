//
// Created by Tomer Amir on 07/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLEPIECE_H
#define PUZZLESOLVER_PUZZLEPIECE_H

#include <string>

using std::string;

class PuzzlePiece {
public:
    int id;
    int rotation = 0;
    int sides[4];

    PuzzlePiece(int id, int l, int t, int r, int b);

    void rotate(int rotation);

    string getRotation() const;

    int left() const;

    int top() const;

    int right() const;

    int bottom() const;

    static bool compare(const PuzzlePiece &piece1, const PuzzlePiece &piece2)
    {
        return piece1.id < piece2.id;
    }
};


#endif //PUZZLESOLVER_PUZZLEPIECE_H
