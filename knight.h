#ifndef KNIGHT_H
#define KNIGHT_H
#include <vector>
#include <string>
#include "piece.h" 
using namespace std;

class Knight : public Piece {

    public:
        Knight(bool isWhite, int row, int col); 
        bool checkValidMove(ChessBoard& board, int toRow, int toCol) override;
        virtual ~Knight() = default;

};

#endif
