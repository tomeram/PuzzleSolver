//
// Created by Tomer Amir on 07/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLEPIECE_H
#define PUZZLESOLVER_PUZZLEPIECE_H


class PuzzlePiece {
public:
    int id;
    int l;
    int t;
    int r;
    int b;

    PuzzlePiece(int id, int l, int t, int r, int b);
    ~PuzzlePiece();

    void print() const;

    static bool compare(const PuzzlePiece &piece1, const PuzzlePiece &piece2)
    {
        return piece1.id < piece2.id;
    }
};


#endif //PUZZLESOLVER_PUZZLEPIECE_H
