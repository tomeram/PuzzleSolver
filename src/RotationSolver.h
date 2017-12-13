//
// Created by dell on 12/12/2017.
//

#ifndef PUZZLESOLVER_ROTATIONSOLVER_H
#define PUZZLESOLVER_ROTATIONSOLVER_H
#include "PuzzlePiece.h"
#include "TypesMap.h"
#include <vector>
using namespace std;


class RotationSolver {
private:
    vector<vector<PuzzlePiece>> matrix;
public:
    RotationSolver(vector<vector<PuzzlePiece>> &matrix);
    int getPair(int p);
    bool fillRow( int rowSize, int colSize, int row , int col_left , int col_rigth, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap );
    bool topRow( int rowSize, int colSize, int row_top , int col_left , int col_rigth, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap );
    bool bottomRow( int rowSize, int colSize, int row_bott , int col_left , int col_rigth, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap );
    bool fillCol( int rowSize, int colSize, int col , int row_top , int row_bott, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap );
    bool leftCol( int rowSize, int colSize, int col_left , int row_top , int row_bott, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap );
    bool rigthCol( int rowSize, int colSize, int col_rigth , int row_top , int row_bott, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap );
    bool fillFrames( int rowSize, int colSize , int row_top, int row_bott,
                int col_left, int col_rigth, vector< vector< PuzzlePiece*>> matrix );

};


#endif //PUZZLESOLVER_ROTATIONSOLVER_H
