#ifndef HUMAN_H
#define HUMAN_H
#include <vector>
#include <string> 
#include "player.h"
#include "chessBoard.h"
using namespace std;

class Human : public Player {
    public:
        Human(bool isWhite); 
        bool makeMove(ChessBoard& board) override;
        virtual ~Human() = default;

};

#endif
