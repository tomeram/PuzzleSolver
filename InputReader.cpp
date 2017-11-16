//
// Created by Tomer Amir on 07/11/2017.
//

#include "InputReader.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <stdexcept>
using namespace std;

bool isPuzzle( int id , int a, int b, int c, int d){
    if ( !( a == 1 || a==0 || a==-1) ){ return false;}
    if ( !( b == 1 || b==0 || b==-1) ){ return false;}
    if ( !( c == 1 || c==0 || c==-1) ){ return false;}
    if ( !( d == 1 || d==0 || d==-1) ){ return false;}
    return true;
}

PazzlePeice* InputReader::readInput(string path) {

    ifstream fin(path);
    if (!fin.good()){
        //error I/O
    }
    string s_name, s_size;
    getline(fin, s_name, '=');
//    if ( NO = ){
//        //error
//    }
    s_name.erase( remove(s_name.begin(), s_name.end(), ' '), s_name.end());
    if ( s_name!="NumElements" ){
        //error
    }

    getline(fin, s_size);
    int size;
    try {
        size = stoi(s_size);
    }
    catch(std::invalid_argument& e){

    }
    catch(std::out_of_range& e){

    }

    string line;
    int id,a,b,c,d;
    int i=0,j=0;
    PazzlePeice* pazzles[size];

    while (getline(fin, line)) {
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);
        if ( tokens.size() != 5) {
            //error pazzle peice should contain 5 elements
        }
        else {
            for (auto &s: tokens) {
//                if ( stoi(s) throw EXCEPTIONS ){
//                    //error the i element is not a int
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
                    }
                }

            if ( !(isPuzzle(id,a,b,c,d)) ){
                //error
                // Puzzle ID id has wrong data: a , b, c, d
            }
            if(j<size){
                pazzles[j] = new PazzlePeice(id,a,b,c,d);
                j++;
            } else{
                //error more pazzele peice then reported
            }
        }
    }
    fin.close();
    return *pazzles;
}

