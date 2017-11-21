//
// Created by Tomer Amir on 07/11/2017.
//

#include "InputReader.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

bool validSide(int side)
{
    return side == 1 || side == 0 || side == -1;
}

bool isPuzzle(int id , int l, int t, int r, int b)
{
    // TODO: Fix ID condition
    if ( !( id == 1 || id == 0 || id == -1) ) {
        return false;
    }

    return validSide(l) && validSide(t) && validSide(r) && validSide(b);
}

void InputReader::readInput(string path, vector<PuzzlePiece> &pieces) throw(int)
{

    ifstream fin(path);

    if (!fin.good()){
        //error I/O
        // TODO
        throw 1;
    }

    string s_name, s_size;
    getline(fin, s_name, '=');
//    if ( NO = ){
    // TODO
//        //error
//    }
    s_name.erase(remove(s_name.begin(), s_name.end(), ' '), s_name.end());
    if ( s_name != "NumElements" ) {
        // TODO
        //error
    }

    getline(fin, s_size);
    int size;

    try {
        size = stoi(s_size);
    }
    catch(std::invalid_argument& e){
        // TODO: Reject
    }
    catch(std::out_of_range& e){
        // TODO: Reject
    }

    string line;
    int id, a, b, c, d;
    int i = 0,j = 0;

    while (getline(fin, line)) {
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);

        if ( tokens.size() != 5) {
            //error pazzle peice should contain 5 elements
            // TODO
        } else {
            for (auto &s: tokens) {
//                if ( stoi(s) throw EXCEPTIONS ){
//                    //error the i element is not a int
                // TODO
//                }

                    switch (i) {
                        case 0  :
                            id = stoi(s);
                            i++;
                            break;
                        case 1  :
                            a = stoi(s);
                            i++;
                            break;
                        case 2  :
                            b = stoi(s);
                            i++;
                            break;
                        case 3  :
                            c = stoi(s);
                            i++;
                            break;
                        case 4  :
                            d = stoi(s);
                            i = 0;
                            break;
                        default:
                            // TODO: Exception
                            break;
                    }
                }

            if ( !(isPuzzle(id,a,b,c,d)) ){
                // TODO
                //error
                // Puzzle ID id has wrong data: a , b, c, d
            }
            if(j < size){
                PuzzlePiece p(id,a,b,c,d);
                pieces.push_back(p);
                j++;
            } else {
                // TODO
                //error more pazzele peice then reported
            }
        }
    }
    fin.close();
}

