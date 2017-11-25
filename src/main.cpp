#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "InputReader.h"
#include "PuzzleSolver.h"

int main(int argc, char** argv)
{
    clock_t begin = clock();

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
        cout << "correct" << endl;
        solver.getSol().print();
    } else {
        cout << "wrong" << endl;
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Total time: " << elapsed_secs << endl;

    return 0;
}
