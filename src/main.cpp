#include <iostream>
#include <fstream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "InputReader.h"
#include "PuzzleSolver.h"

void printUsage(const string &arg0)
{
    cout << "Please supply correct input and output file paths:" << endl
         << arg0 << " <input_file> <output_file> [-rotate]" << endl;
}

int main(int argc, char** argv)
{
    bool rotation = false;

    if (argc < 3 || argc > 4) {
        printUsage(argv[0]);
        return 1;
    }

    if (argc == 4) {
        string rotateFlag = argv[4];

        if (rotateFlag == "-rotate") {
            rotation = true;
        } else {
            printUsage(argv[0]);
            return 1;
        }
    }

    vector<PuzzlePiece> pieces;

    ofstream outputFile;
    outputFile.open((argv[2]));

    InputReader reader(&outputFile);

    try {
        reader.readInput(argv[1], pieces);
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

    if (!reader.valid) {
        outputFile.close();

        return 1;
    }

    Puzzle puzzle(pieces);

    PuzzleSolver solver(puzzle, &outputFile, rotation);

    if (!solver.isValid()) {
        outputFile.close();
        return 1;
    }

    if (solver.solve()) {
        solver.getSol().print(&outputFile);
    } else {
        outputFile << "Cannot solve puzzle: it seems that there is no proper solution" << endl;
    }

    outputFile.close();

    return 0;
}
