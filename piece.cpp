#include "piece.h"

Piece::Piece(bool isWhite): isWhite{isWhite} {}

Piece::~Piece() {}

bool Piece::getIsWhite() const {
    return isWhite;
}

bool Piece::getPieceType() const {
    return pieceType;
}
