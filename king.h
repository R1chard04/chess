#ifndef KING_H
#define KING_H
#include <vector>
#include <string>
#include "piece.h" 
using namespace std;

class King : public Piece {

    public:
        King(string pieceColour, int row, int col);
        virtual bool checkValidMove(ChessBoard& board, int toRow, int toCol) override;
        virtual ~King() = default;

};

#endif
