#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string> 
#include <iostream>
#include <sstream>
#include "chessboard.h"

class Player {

    protected:
        bool isWhite;
        std::istream &in = std::cin;
        std::ostream &out = std::cout;

    public:
        Player(bool isWhite);
        virtual bool makeMove(ChessBoard& board) = 0;
        virtual ~Player() = default;

};

#endif
