#ifndef KING_H
#define KING_H
#include <vector>
#include <string>
#include "piece.h" 
#include "chessboard.h"
using namespace std;

class King : public Piece {

    public:
        King(bool isWhite, int row, int col);
        bool checkValidMove(ChessBoard& board, int toRow, int toCol) override;
        virtual ~King() = default;

};

#endif
