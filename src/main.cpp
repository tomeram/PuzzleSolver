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

	string input, output;

	if (argc == 4) {
		string arg1 = argv[1];
		string arg2 = argv[2];
		string arg3 = argv[3];

		if (arg1 == "-rotate") {
			rotation = true;
			input = argv[2];
			output = argv[3];
		} else if (arg2 == "-rotate") {
			rotation = true;
			input = argv[1];
			output = argv[3];
		} else if (arg3 == "-rotate") {
			rotation = true;
			input = argv[1];
			output = argv[2];
		}

		if (!rotation) {
			printUsage(argv[0]);
			return 1;
		}
	} else {
		input = argv[1];
		output = argv[2];
	}

	vector<PuzzlePiece> pieces;

	ofstream outputFile;
	outputFile.open(output);

	InputReader reader(&outputFile);

	try {
		reader.readInput(input, pieces);
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

//	RotationSolver solver(&puzzle, rotation);

	PuzzleSolver solver(&puzzle, &outputFile, rotation);
	// TODO: Validate
    if (!solver.isValid()) {
        outputFile.close();
        return 1;
    }

	if (solver.solve()) {
		solver.getSol().print(&outputFile, rotation, puzzle);
	} else {
		outputFile << "Cannot solve puzzle: it seems that there is no proper solution" << endl;
	}

	outputFile.close();

	return 0;
}
