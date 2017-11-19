//
// Created by Tomer Amir on 07/11/2017.
//

#include "InputReader.h"
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

bool isPuzzle( int a, int b, int c, int d){
    if ( !( a == 1 || a==0 || a==-1) ){ return false;}
    if ( !( b == 1 || b==0 || b==-1) ){ return false;}
    if ( !( c == 1 || c==0 || c==-1) ){ return false;}
    if ( !( d == 1 || d==0 || d==-1) ){ return false;}
    return true;
}
struct piece{
    int size = 0;
    long int elements[5] ={0};
};


PuzzlePiece* InputReader::readInput(string pathIn , string pathOut ) {
    // Open the file to read
    ifstream fin(pathIn);
    if (!fin.good()){
        cout << "Error : Opening file " << pathIn << endl;
        return nullptr;
    }
    // Handling part of the first row of the file.
    string s_name, s_size;
    getline(fin, s_name, '=');
    s_name.erase( remove(s_name.begin(), s_name.end(), ' '), s_name.end());
    if ( s_name!="NumElements" ){
        cout << "NOT IN THE RIGHT PORMAT" << endl;
        fin.close();
        return nullptr;
    }
    // Handling the size of the puzzle.
    getline(fin, s_size);
    long int size =0;
    try {
        size = stoi(s_size);
    }
    catch(std::invalid_argument& e){
        cout << "Error : Number parts of the puzzle is invalid."<< endl;
        fin.close();
        return nullptr;
    }
    catch(std::out_of_range& e){
        cout << "Error : The parts of the puzzle can be up to 10,000,000" << endl;
        fin.close();
        return nullptr;
    }

    string line;
    long int a=0, i=0;
    long t=0;
    auto puzzles = new PuzzlePiece*[size];
    piece piece;
    list <long int>  Missing_elements;
    long int* elements = new long int[size];
    fill_n(elements,size,0);
    list <long int> Wrong_element;
    map<long int, string> Wrong_format;

    // Extracting puzzle lines.
    while (getline(fin, line)) {
        // Split the line by WhiteSpace.
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);

        // Check character validity.
        for (auto &s: tokens) {
            try {
                a = stoi(s);
            }
            catch (std::invalid_argument &e) {
                cout << "Error : Number parts of the puzzle is invalid." << endl;
                delete[] elements;
                delete[] puzzles;
                fin.close();
                return nullptr;
            }
            catch (std::out_of_range &e) {
                cout << "Error : Number can be up to 10,000,000" << endl;
                delete[] elements;
                delete[] puzzles;
                fin.close();
                return nullptr;
            }
            piece.elements[i] = a;
            piece.size++;
            i++;
        }

        // Error checking
        if (piece.size > 0) {
            if (piece.size == 5) { //All four corners are there
                if (!(isPuzzle(piece.elements[1], piece.elements[2], piece.elements[3],
                               piece.elements[4]))) { // The line in the puzzle is invalid
                    Wrong_format[piece.elements[0]] = line;
                } else { // The line in the puzzle is valid
                    if ( piece.elements[0] <= size && piece.elements[0] > 0) { //The ID of the puzzle is valid
                        puzzles[ piece.elements[0] -1 ] = new PuzzlePiece(piece.elements[0],
                                piece.elements[1], piece.elements[2], piece.elements[3], piece.elements[4]);
                        elements[ piece.elements[0] -1 ]= 1; //Mark that the part is not missing
                    } else { //The ID of the puzzle is invalid
                        Wrong_element.push_back( piece.elements[0] );
                    }
                }
            } else { //Missing corners
                if ( !(piece.elements[0] <= size && piece.elements[0] > 0) ) { //The ID of the puzzle is invalid
                    Wrong_element.push_back( piece.elements[0] );
                }
                Wrong_format[piece.elements[0]] = line;
            }
        }
        piece.size = 0;
        i = 0;
    }

    // Checking the missing puzzle pieces
    for ( i= 0 ; i< size ; i++) {
        if ( elements[i] == 0){
            Missing_elements.push_back(i+1);
        }
    }

    ofstream fout( pathOut ); //Open the file to write errors

    if ( Missing_elements.size() > 0 ){
        t = Missing_elements.size() - 1;
        fout << "Missing puzzle element(s) with the following IDs: ";
        for (auto &num: Missing_elements) {
            fout << num ;
            if ( t > 0){
                fout << ", " ;
                t--;
            }
        }
        fout << "" << endl;
    }

    if (Wrong_element.size() > 0 ){
        t = Wrong_element.size() - 1;
        fout << "Puzzle of size " << size << " cannot have the following IDs: " ;
        for (auto &num: Wrong_element) {
            fout << num ;
            if ( t > 0){
                fout << ", " ;
                t--;
            }
        }
        fout << "" << endl;
    }

    if ( Wrong_format.size() > 0 ){
        for (auto & element: Wrong_format) {
            fout << "Puzzle ID " << element.first << " has wrong data: "<< element.second << endl;
        }
    }
    delete[] elements;
    delete[] puzzles;
    fin.close();
    fout.close();

    if ( Missing_elements.size() > 0 || Wrong_element.size() > 0|| Wrong_format.size() > 0 ){
        return nullptr;
    }
    return *puzzles;
}

int main() {
    InputReader ip;
    ip.readInput("C:/Users/dell/Desktop/test.txt" , "C:/Users/dell/Desktop/out.txt");
    return 0;
}