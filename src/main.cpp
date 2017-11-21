#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "InputReader.h"
#include "PuzzleSolver.h"

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

    PuzzleSolver solver(puzzle);

    bool t = solver.solve();

    cout << "The result is ";

    if (t) {
        cout << "correct";
    } else {
        cout << "wrong";
    }

    cout << endl;

    return 0;
}
