#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "InputReader.h"

int main(int argc, char** argv)
{
    if (argc != 3) {
        cout << "Please supply input and output file paths:" << endl << argv[0] << " <input_file> <output_file>";
        return 1;
    }

    vector<PuzzlePiece> pieces;

    try {
        InputReader::readInput(argv[1], pieces);
    } catch (int e) {
        cout << "Error: " << e << endl;
        return 1;
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
