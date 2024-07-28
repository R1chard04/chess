#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string>

class ChessBoard; // Forward declaration

using namespace std;

class Piece {
protected:
    bool isWhite;
    vector<vector<int>> moves;
    char pieceType;
    int row, col;
    bool hasMoved;

public:
    Piece(bool isWhite, vector<vector<int>> moves, char pieceType, int row, int col);
    virtual ~Piece();

    virtual bool checkValidMove(ChessBoard& board, int toRow, int toCol) = 0;

    bool getIsWhite() const;
    char getPieceType() const;  // Corrected return type
    bool getHasMoved() const;
    int getRow() const;
    int getCol() const;
    void setHasMoved(bool hasMoved);
    void setCoords(int row, int col);
};

#endif
