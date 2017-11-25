#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "InputReader.h"
#include "PuzzleSolver.h"

void printUsage(const string &arg0)
{
    cout << "Please supply correct input and output file paths:" << endl
         << arg0 << " <input_file> <output_file>" << endl;
}

int main(int argc, char** argv)
{
    clock_t begin = clock();

    if (argc != 3) {
        printUsage(argv[0]);
        return 1;
    }

    vector<PuzzlePiece> pieces;

    try {
        InputReader::readInput(argv[1], pieces);
    } catch (int e) {
        switch (e) {
            case 1:
                printUsage(argv[0]);
                break;
            case 2:
                cout << "Invalid file format" << endl;
                break;
            case 3:
                // General Error - handled in InputReader
                break;
            default:
                cout << "Unhandled exception: " << e << endl;
                break;
        }

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
