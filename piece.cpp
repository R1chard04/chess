#include "piece.h"

Piece::Piece(bool isWhite, vector<vector<int>> moves, char pieceType, int row, int col)
    : isWhite{isWhite}, moves{moves}, pieceType{pieceType}, row{row}, col{col}, hasMoved{false} {}

Piece::~Piece() {}


bool Piece::getIsWhite() const {
    return isWhite;
}

char Piece::getPieceType() const {  // Corrected return type
    return pieceType;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

int Piece::getRow() const {
    return row;
}

int Piece::getCol() const {
    return col;
}

void Piece::setHasMoved(bool hasMoved) {
    this->hasMoved = hasMoved;
}

void Piece::setCoords(int row, int col) {
    this->row = row;
    this->col = col;
}
