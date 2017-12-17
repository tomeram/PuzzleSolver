//
// Created by Tomer Amir on 12/12/2017.
//

#ifndef PUZZLESOLVER_TYPESMAP_H
#define PUZZLESOLVER_TYPESMAP_H

#include <set>
#include <map>
#include <string>
#include <vector>
#include "Puzzle.h"

using namespace std;

class TypesMap {
public:
    class Constraints : public PuzzlePiece {
    private:
        friend class TypesMap;
    public:
        Constraints();
        Constraints(int l, int t, int r, int b);
        friend bool operator< (const Constraints &left, const Constraints &right);
    };

private:
    map<string, vector<int>> _types;
    Puzzle *_puzzle;
    bool _rotate;

public:
    explicit TypesMap(Puzzle *puzzle, bool rotate = false);

    vector<int> &operator[](string type);

    vector<Constraints> getTypes(Constraints c) const;

    PuzzlePiece* getPiece(Constraints type);

	void addPiece(PuzzlePiece *piece);

	int size();

	bool empty();

	int countBottomEdges();

	void sumPieces(int &hor, int &ver);
};


#endif //PUZZLESOLVER_TYPESMAP_H
