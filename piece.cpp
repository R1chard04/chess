#include "piece.h"

Piece::Piece(string pieceColour): pieceColour{pieceColour} {}

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


