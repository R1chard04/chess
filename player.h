#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string> 
#include "chessBoard.h"
using namespace std;

class Player {
    public:
        Player(); 
        bool makeMove(ChessBoard& board);
        virtual ~Player() = default;

};

#endif
