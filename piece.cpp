#include "piece.h"

Piece::Piece(string pieceColour, vector<vector<int>> moves, char pieceType): pieceColour{pieceColour}, moves{moves}, pieceType{pieceType} {}

Piece::~Piece() {}

bool Piece::getIsWhite() const {
    return pieceColour == "white";
}

bool Piece::getPieceType() const {
    return pieceType;    
}

vector<vector<int> > Piece::getValidMoves() {
    return moves;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}
