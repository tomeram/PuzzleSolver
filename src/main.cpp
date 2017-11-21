#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "InputReader.h"

int main(int argc, char** argv)
{
    InputReader reader;

    for (int  i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }

    vector<PuzzlePiece> pieces;

    try {
        reader.readInput("../test.txt", pieces);

        cout << "Success" << endl;
    } catch (int e) {
        cout << "Error: " << e << endl;
    }

//    int i;
//    vector<PuzzlePiece> pieces;
//
//    for (i = 1; i <= 1; i++)
//    {
//        PuzzlePiece test(i, 0, 0, 0, 0);
//        pieces.push_back(test);
//        test.print();
//    }

//    PuzzlePiece test1(1, 0, 0, 1, 1);
//    pieces.push_back(test1);
//
//    PuzzlePiece test2(2, -1, 0, 0, 0);
//    pieces.push_back(test2);
//
//    PuzzlePiece test3(3, 0, -1, 0, 0);
//    pieces.push_back(test3);
//
//    PuzzlePiece test4(4, 0, 0, 0, 0);
//    pieces.push_back(test4);

    Puzzle puzzle(pieces);

    vector<unsigned int> row1;
    row1.push_back(1);
    row1.push_back(2);

    puzzle.addRow(row1);

    vector<unsigned int> row2;
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
