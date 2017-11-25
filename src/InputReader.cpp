//
// Created by Tomer Amir on 07/11/2017.
//

#include "InputReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define PathError 1;
#define InputFormat 2;
#define GeneralError 3;

using namespace std;

bool isinteger(std::string const& n) noexcept
{
    if (std::isdigit(n[0]) || (n.size() > 1 && (n[0] == '-' || n[0] == '+')))
    {
        for (std::string::size_type i{ 1 }; i < n.size(); ++i)
            if (!std::isdigit(n[i]))
                return false;

        return true;
    }
    return false;
}

bool validSide(int side)
{
    return side == 1 || side == 0 || side == -1;
}

bool validatePiece(int l, int t, int r, int b)
{
    return validSide(l) && validSide(t) && validSide(r) && validSide(b);
}

void InputReader::readInput(string path, vector<PuzzlePiece> &pieces) throw(int)
{
    ifstream fin(path);

    if (!fin.good()){
        throw PathError;
    }

    string s_name, s_size;
    getline(fin, s_name, '=');

    if (s_name.empty()) {
        throw InputFormat;
    }

    string::size_type location = s_name.find(' ');
    s_name = s_name.substr(0, location);

    if (s_name != "NumElements") {
        throw InputFormat;
    }

    getline(fin, s_size);
    int size;

    size = stoi(s_size);

    string line;
    int id, a, b, c, d;
    int i = 0,j = 0;

    while (getline(fin, line)) {
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);

        if (tokens.size() != 5) {
            cout << "Puzzle ID " << tokens.at(0) << " has wrong data: " << line << endl;
            throw GeneralError;
        } else {
            for (auto &s: tokens) {
                if (!isinteger(s)) {
                    cout << "Puzzle ID " << tokens.at(0) << " has wrong data: " << line << endl;
                    throw GeneralError;
                }

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
                        cout << "Puzzle ID " << tokens.at(0) << " has wrong data: " << line << endl;
                        throw GeneralError;
                }
            }

            if (!validatePiece(a, b, c, d)){
                cout << "Puzzle ID " << tokens.at(0) << " has wrong data: " << line << endl;
                throw GeneralError;
            }

            PuzzlePiece p(id, a, b, c, d);
            pieces.push_back(p);
            j++;
        }
    }
    fin.close();
}

