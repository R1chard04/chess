#ifndef BISHOP_H
#define BISHOP_H
#include <vector>
#include <string> 
#include "piece.h"
#include "chessboard.h"
using namespace std;

class Bishop : public Piece {

    public:
        Bishop(string pieceColour, int row, int col); 
        bool checkValidMove(ChessBoard& cBoard, int toRow, int toCol) override;
        virtual ~Bishop() = default;
};

#endif
