#ifndef COMPUTER_H
#define COMPUTER_H
#include <vector>
#include <string> 
#include "player.h"
#include "chessBoard.h"
using namespace std;

class Computer : public Player {
    public:
        Computer(); 
        bool makeMove(ChessBoard& board);
        virtual ~Computer() = default;

};

#endif
