#include "piece.h"

Piece::Piece(string pieceColour, vector<vector<int>> moves, char pieceType, int row, int col): pieceColour{pieceColour}, moves{moves}, pieceType{pieceType}, row{row}, col{col} {}

Piece::~Piece() {}

bool Piece::getIsWhite() const {
    return pieceColour == "white";
}

bool Piece::getPieceType() const {
    return pieceType;    
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setHasMoved(bool hasMoved) {
    this->hasMoved = hasMoved;
}

void Piece::setCoords(int row, int col) {
    this->row = row;
    this->col = col;
}
