#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"

int main()
{
//    int i;
    vector<PuzzlePiece> pieces;
//
//    for (i = 1; i <= 1; i++)
//    {
//        PuzzlePiece test(i, 0, 0, 0, 0);
//        pieces.push_back(test);
//        test.print();
//    }

    PuzzlePiece test1(1, 0, 0, 1, 1);
    pieces.push_back(test1);

    PuzzlePiece test2(2, -1, 0, 0, 0);
    pieces.push_back(test2);

    PuzzlePiece test3(3, 0, -1, 0, 0);
    pieces.push_back(test3);

    PuzzlePiece test4(4, 0, 0, 0, 0);
    pieces.push_back(test4);

    Puzzle puzzle(pieces);

    vector<int> row1;
    row1.push_back(1);
    row1.push_back(2);

    puzzle.addRow(row1);

    vector<int> row2;
    row2.push_back(3);
    row2.push_back(4);

    puzzle.addRow(row2);

    bool t = PuzzleValidator::validate(puzzle);

    cout << "The result is ";

    if (t) {
        cout << "correct";
    } else {
        cout << "wrong";
    }

    cout << endl;

    return 0;
}
