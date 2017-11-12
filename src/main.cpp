#include <iostream>

#include "PuzzlePiece.h"
#include "PuzzleValidator.h"
#include "Puzzle.h"

int main()
{
    int i;

    Puzzle p;

    for (i = 1; i <= 10; i++)
    {
        PuzzlePiece test(i, 1, 1, 1, 1);
        test.print();
    }
    
    return 0;
}
