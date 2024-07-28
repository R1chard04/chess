#ifndef ROOK_H
#define ROOK_H
#include <vector>
#include <string>
#include "piece.h" 
using namespace std;

class Rook : public Piece {

    public:
        Rook(string pieceColour, int row, int col); 
        bool checkValidMove(ChessBoard& cBoard, int toRow, int toCol) override;
        virtual ~Rook() = default;
};

#endif
