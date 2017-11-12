//
// Created by Tomer Amir on 07/11/2017.
//

#ifndef PUZZLESOLVER_PUZZLEPIECE_H
#define PUZZLESOLVER_PUZZLEPIECE_H


class PuzzlePiece {
public:
    PuzzlePiece(int id, int l, int t, int r, int b);
    ~PuzzlePiece();

public:
    int id;

    int l;
    int t;
    int r;
    int b;
    
    void print();
};


#endif //PUZZLESOLVER_PUZZLEPIECE_H
