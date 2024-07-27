#ifndef COMPUTER_H
#define COMPUTER_H
#include <vector>
#include <string> 
#include "player.h"
#include "chessBoard.h"
using namespace std;

class Computer : public Player {

    int difficulty;

    public:
        Computer(bool isWhite, int difficulty); 
        bool makeMove(ChessBoard& board) override;
        virtual ~Computer() = default;

};

#endif
