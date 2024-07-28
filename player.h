#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string> 
#include <iostream>
#include <sstream>
#include "chessboard.h"
using namespace std;

class Player {

    protected:
        bool isWhite;
        std::istream &in = cin;
        std::ostream &out = cout;

    public:
        Player(bool isWhite); // TODO: maybe add some params here 
        virtual bool makeMove(ChessBoard& board) = 0;
        virtual ~Player() = default;

};

#endif
