#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string> 
#include "chessboard.h"

using namespace std;

class Piece {
    string pieceColour; 
    char pieceType;
    bool hasMoved;
    
    protected: 
        vector<vector<int>> moves; 
        int row, col; 

    public:
        Piece(string pieceColour, vector<vector<int>> moves, char pieceType, int row, int col);

        string getColour(); 
        virtual bool checkValidMove(ChessBoard& board, int toRow, int toCol) = 0;

        virtual ~Piece() = default;

        bool getIsWhite() const;
        bool getPieceType() const;
        bool getHasMoved() const;
        int getRow() const;
        int getCol() const;
        void setHasMoved(bool hasMoved);
        void setCoords(int row, int col);

};

#endif
