#ifndef PAWN_H
#define PAWN_H
#include <vector>
#include <string>
#include "piece.h" 
using namespace std;

class Pawn : public Piece {

    public:
        Pawn(string pieceColour, int row, int col); 
        bool checkValidMove(ChessBoard& board, int toRow, int toCol) override;
        virtual ~Pawn() = default;
};

#endif
