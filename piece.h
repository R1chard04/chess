#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string>

class ChessBoard;

class Piece {
protected:
    bool isWhite;
    std::vector<std::vector<int>> moves;
    char pieceType;
    int row, col;
    bool hasMoved;
    int value; 

public:
    Piece(bool isWhite, std::vector<std::vector<int>> moves, char pieceType, int row, int col, int value);
    virtual ~Piece();

    virtual bool checkValidMove(ChessBoard& board, int toRow, int toCol) = 0;

    bool getIsWhite() const;
    char getPieceType() const;  // Corrected return type
    bool getHasMoved() const;
    int getRow() const;
    int getCol() const;
    int getValue() const; 
    void setHasMoved(bool hasMoved);
    void setCoords(int row, int col);
};

#endif
