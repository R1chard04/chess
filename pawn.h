#ifndef PAWN_H
#define PAWN_H
#include <vector>
#include <string>
#include "piece.h" 
#include "chessboard.h"

class Pawn : public Piece {

    public:
        Pawn(bool isWhite, int row, int col); 
        bool checkValidMove(ChessBoard& board, int toRow, int toCol) override;
        virtual ~Pawn() = default;
};

#endif
