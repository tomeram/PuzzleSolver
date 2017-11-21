#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "InputReader.h"
#include "PuzzleSolution.h"

int main(int argc, char** argv)
{
    if (argc != 3) {
        cout << "Please supply input and output file paths:" << endl
             << argv[0] << " <input_file> <output_file>" << endl;
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

    PuzzleSolution solution;

    bool t = PuzzleValidator::validate(puzzle, solution);

    cout << "The result is ";

    if (t) {
        cout << "correct";
    } else {
        cout << "wrong";
    }

    cout << endl;

    return 0;
}
