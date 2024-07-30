#ifndef COMPUTER_H
#define COMPUTER_H
#include <vector>
#include <string> 
#include "player.h"
#include "chessboard.h"

class Computer : public Player {

    int difficulty;
    std::vector<std::vector<int> > generateMoves(ChessBoard& board);

    bool makeMove1(ChessBoard& cBoard);  
    bool makeMove2(ChessBoard& cBoard);  
    bool makeMove3(ChessBoard& cBoard);  
    bool makeMove4(ChessBoard& cBoard);  

    public:
        Computer(bool isWhite, int difficulty); 
        bool makeMove(ChessBoard& board) override;
        virtual ~Computer() = default;

};

#endif
