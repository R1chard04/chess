#ifndef QUEEN_H
#define QUEEN_H
#include <vector>
#include <string>
#include "piece.h" 
#include "chessboard.h"
using namespace std;

class Queen : public Piece {

    public:
        Queen(bool isWhite, int row, int col); 
        bool checkValidMove(ChessBoard& cBoard, int toRow, int toCol) override;
        virtual ~Queen() = default;

};

#endif
