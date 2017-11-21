#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "InputReader.h"

int main(int argc, char** argv)
{
    if (argc != 3) {
        cout << "Please supply input and output file paths:" << endl << "./ex1 <input_file> <output_file>";
        exit(1);
    }

    InputReader reader;
    vector<PuzzlePiece> pieces;

    try {
        string input = argv[1];
        reader.readInput(input, pieces);
    } catch (int e) {
        cout << "Error: " << e << endl;
        exit(1);
    }

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
