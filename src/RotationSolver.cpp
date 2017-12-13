//
// Created by dell on 12/12/2017.
//

#include "RotationSolver.h"

//RotationSolver::matrix()
//int m = colSize, n = rowSize;
//
//for(int i = 0 ; i < m ; ++i){
//    //Grow Columns by n
//    matrix[i].resize(n);
//}

int getPair( int p) {
    return -p;
}

bool fillRow( int rowSize, int colSize, int row , int col_left , int col_rigth, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap){
    if ( col_left > col_rigth ){
        return true;
    }
    else{
        TypesMap::Constraints c;
        if ( col_left-1 > 0){
            PuzzlePiece* myLeft = matrix[col_left-1][row];
            if ( myLeft == nullptr){
                c.left(-2);
            }else{
                c.left(getPair( myLeft->left() ));
            }

        } else{
            c.left(0);
        }

        if ( row-1 > 0){
            PuzzlePiece* myTop = matrix[col_left][row-1];
            if ( myTop== nullptr){
                c.top(-2);
            }else{
                c.top(getPair( myTop->top() ));
            }
        } else{
            c.top(0);
        }

        if ( row+1 < rowSize){
            PuzzlePiece* myBottom = matrix[col_left][row+1];
            if ( myBottom== nullptr){
                c.bottom(-2);
            }else{
                c.bottom( getPair( myBottom->bottom() ));
            }
        } else{
            c.bottom(0);
        }

        if ( col_left+1 < colSize){
            PuzzlePiece* myRigth = matrix[col_left+1][row];
            if ( myRigth== nullptr){
                c.right(-2);
            }else{
                c.right(getPair( myRigth->right() ));
            }
        } else{
            c.right(0);
        }

        vector<string> list =  typesMap.getTypes(c);

        for (string type : list ){
            TypesMap newMap = typesMap;
            PuzzlePiece* piece = newMap.getPiece(type);
            if ( piece != nullptr ){
                matrix[col_left][row]= piece;
                bool b= fillRow( rowSize, colSize, row , col_left+1 , col_rigth , matrix, newMap );
                if ( b == true ){
                    return true;
                }
                else{
                    matrix[col_left][row]= nullptr;
                }
            }
        }
        return false;
    }
}


bool topRow( int rowSize, int colSize, int row_top , int col_left , int col_rigth, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap ){
    return fillRow( rowSize, colSize, row_top , col_left , col_rigth, matrix, typesMap );
}

bool bottomRow( int rowSize, int colSize, int row_bott , int col_left , int col_rigth, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap ){
    return fillRow( rowSize, colSize, row_bott , col_left , col_rigth, matrix, typesMap );
}

bool fillCol( int rowSize, int colSize, int col , int row_top , int row_bott, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap ){
    if ( row_top > row_bott ){
        return true;
    }
    else{
        TypesMap::Constraints c;
        if ( col-1 > 0){
            PuzzlePiece* myLeft = matrix[col-1][row_top];
            if ( myLeft== nullptr){
                c.left(-2);
            }else{
                c.left(getPair( myLeft->left() ));
            }

        } else{
            c.left(0);
        }

        if ( col+1 < colSize){
            PuzzlePiece* myTop = matrix[col+1][row_top];
            if ( myTop== nullptr){
                c.top(-2);
            }else{
                c.top(getPair( myTop->top() ));
            }
        } else{
            c.top(0);
        }

        if ( row_top+1 < rowSize){
            PuzzlePiece* myBottom = matrix[col][row_top+1];
            if ( myBottom== nullptr){
                c.bottom(-2);
            }else{
                c.bottom( getPair( myBottom->bottom() ));
            }
        } else{
            c.bottom(0);
        }

        if ( row_top-1 > 0){
            PuzzlePiece* myRigth = matrix[col][row_top-1];
            if ( myRigth== nullptr){
                c.right(-2);
            }else{
                c.right(getPair( myRigth->right() ));
            }
        } else{
            c.right(0);
        }

        vector<string> list = typesMap.getTypes(c);
        if (! list.empty() ){
            for (string type : list ){
                TypesMap newMap = typesMap;
                PuzzlePiece* piece = newMap.getPiece(type);
                if ( piece != nullptr ){
                    matrix[col][row_top]= piece;
                    bool b= fillCol( rowSize, colSize, col , row_top+1 , row_bott , matrix, newMap );
                    if ( b == true ){
                        return true;
                    }
                    else{
                        matrix[col][row_top]= nullptr;
                    }
                }
            }
            return false;
        }
        else{
            return false;
        }
    }
}

bool leftCol( int rowSize, int colSize, int col_left , int row_top , int row_bott, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap ){
    return fillCol( rowSize, colSize, col_left , row_top , row_bott, matrix, typesMap );
}

bool rigthCol( int rowSize, int colSize, int col_rigth , int row_top , int row_bott, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap ){
    return fillCol( rowSize, colSize, col_rigth , row_top , row_bott, matrix, typesMap );
}

bool fillFrames( int rowSize, int colSize , int row_top, int row_bott,
                 int col_left, int col_rigth, vector< vector< PuzzlePiece*>> matrix, TypesMap &typesMap ) {

    if (col_left > col_rigth && row_top > row_bott ) {
        return true;

    }

    if (col_left < col_rigth && row_top < row_bott) {
        if ( topRow(rowSize, colSize, row_top , col_left , col_rigth, matrix, typesMap) &&
             bottomRow( rowSize, colSize, row_bott , col_left , col_rigth, matrix, typesMap ) &&
             rigthCol( rowSize, colSize, col_rigth , row_top , row_bott, matrix, typesMap ) &&
             leftCol( rowSize, colSize, col_left , row_top , row_bott, matrix, typesMap ) && true ){
            fillFrames( rowSize, colSize, row_top + 1, row_bott - 1, col_left +1 , col_rigth -1 , matrix, typesMap);
        } else{
            return false;
        }
    }

    if (col_left == col_rigth && row_top < row_bott) {
        if ( topRow(rowSize, colSize, row_top , col_left , col_rigth, matrix, typesMap) &&
             bottomRow( rowSize, colSize, row_bott , col_left , col_rigth, matrix, typesMap ) &&
             leftCol( rowSize, colSize, col_left , row_top , row_bott, matrix, typesMap ) && true ){
            fillFrames( rowSize, colSize, row_top + 1, row_bott - 1, col_left +1 , col_rigth, matrix, typesMap);
        } else{
            return false;
        }
    }
    if (col_left < col_rigth && row_top == row_bott) {
        if ( leftCol(rowSize, colSize, col_left , row_top , row_bott, matrix, typesMap) &&
             rigthCol( rowSize, colSize, col_rigth , row_top , row_bott, matrix, typesMap ) &&
             topRow( rowSize, colSize, row_top , col_left , col_rigth, matrix, typesMap ) && true ){
            fillFrames( rowSize, colSize, row_top + 1, row_bott , col_left +1 , col_rigth -1, matrix, typesMap);
        } else{
            return false;
        }
    }
    if (col_left == col_rigth && row_top == row_bott) {
        if ( topRow(rowSize, colSize, row_top , col_left , col_rigth, matrix, typesMap) &&
             leftCol( rowSize, colSize, col_left , row_top , row_bott, matrix, typesMap ) && true ){
            fillFrames( rowSize, colSize, row_top + 1, row_bott , col_left +1 , col_rigth, matrix, typesMap);
        } else{
            return false;
        }
    }
    if (col_left < col_rigth && row_top > row_bott) {
        if ( leftCol(rowSize, colSize, col_left , row_top , row_bott, matrix, typesMap) &&
             rigthCol( rowSize, colSize, col_rigth , row_top , row_bott, matrix, typesMap ) && true ){
            fillFrames( rowSize, colSize, row_top, row_bott , col_left +1 , col_rigth -1, matrix, typesMap);
        } else{
            return false;
        }
    }
    if (col_left > col_rigth && row_top < row_bott) {
        if ( topRow(rowSize, colSize, row_top , col_left , col_rigth, matrix, typesMap) &&
             bottomRow( rowSize, colSize, row_bott , col_left , col_rigth, matrix, typesMap ) && true ){
            fillFrames( rowSize, colSize, row_top+1, row_bott-1 , col_left , col_rigth, matrix, typesMap);
        } else{
            return false;
        }
    }
    return false;
}


