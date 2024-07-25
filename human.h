#ifndef HUMAN_H
#define HUMAN_H
#include <vector>
#include <string> 
#include "player.h"
#include "chessBoard.h"
using namespace std;

class Human : public Player {
    public:
        Human(); 
        bool makeMove(ChessBoard& board);
        virtual ~Human() = default;

};

#endif
