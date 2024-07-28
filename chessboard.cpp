#include "chessboard.h"
#include "piece.h"
#include <iostream> 
#include <vector> 
using namespace std; 

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
}

ChessBoard::~ChessBoard() {}

void ChessBoard::attach(Observer* o) {
    observers.emplace_back(o);
}

void ChessBoard::detach(Observer* o) {
    for (int i = 0; i < observers.size(); ++i) {
        if (observers[i] == o) {
            observers.erase(observers.begin() + i);
            break;
        }
    }
}

void ChessBoard::notifyObservers() {
    for (int i = 0; i < observers.size(); ++i) {
        observers[i]->notify();
    }
}

Piece* ChessBoard::getSquare(int row, int col) {
    return board[row][col];
}

void ChessBoard::removePiece(int row, int col) {
    Piece *p = getSquare(row, col);
    if (p == nullptr) { return; }

    if (p->getIsWhite()) {
        for (int i = 0; i < whitePieces.size(); ++i) {
            if (whitePieces[i].get() == p) {
                whitePieces.erase(whitePieces.begin() + i);
                break;
            }
        }
    } else {
        for (int i = 0; i < blackPieces.size(); ++i) {
            if (blackPieces[i].get() == p) {
                blackPieces.erase(blackPieces.begin() + i);
                break;
            }
        }
    }

    board[row][col] = nullptr;
}

void ChessBoard::placePiece(int row, int col, bool isWhite, char pieceType, bool moved) {
    if (getSquare(row, col) != nullptr) {
        removePiece(row, col);
    }

    unique_ptr<Piece> p;

    if (pieceType == 'p') { p = make_unique<Pawn>(isWhite, row, col); } 
    else if (pieceType == 'r') { p = make_unique<Rook>(isWhite, row, col); } 
    else if (pieceType == 'n') { p = make_unique<Knight>(isWhite, row, col); } 
    else if (pieceType == 'b') { p = make_unique<Bishop>(isWhite, row, col); } 
    else if (pieceType == 'q') { p = make_unique<Queen>(isWhite, row, col); } 
    else if (pieceType == 'k') { p = make_unique<King>(isWhite, row, col); }
    p.get()->setHasMoved(moved);

    board[row][col] = p.get();
    notifyObservers();
    if (isWhite) {
        whitePieces.emplace_back(move(p));
    } else {
        blackPieces.emplace_back(move(p));
    }
}

void ChessBoard::removeAllPieces() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            removePiece(i, j);
        }
    }
}

Piece* ChessBoard::getKing(bool isWhite) {
    if (isWhite) {
        for (int i = 0; i < whitePieces.size(); ++i) {
            if (whitePieces[i].get()->getPieceType() == 'k') {
                return whitePieces[i].get();
            }
        }
    } else {
        for (int i = 0; i < blackPieces.size(); ++i) {
            if (blackPieces[i].get()->getPieceType() == 'k') {
                return blackPieces[i].get();
            }
        }
    }
    return nullptr;
}

bool existsPieceInSquare(ChessBoard& board, int row, int col, char pieceType = ' ', bool isWhite = true) {
    if (pieceType == ' ') {
        return board.getSquare(row, col) != nullptr;
    }
    Piece* tmpPiece = board.getSquare(row, col);
    return tmpPiece != nullptr && tmpPiece->getPieceType() == pieceType && (tmpPiece->getIsWhite() && isWhite || !tmpPiece->getIsWhite() && !isWhite);
}

bool existsPieceInHorizontal(ChessBoard& board, int row, int col, char pieceType = ' ', bool isWhite = true) {
    int i = col;

    while (i < 8) {
        if ((pieceType != ' ' && existsPieceInSquare(board, row, i, pieceType, isWhite)) || (pieceType == ' ' && existsPieceInSquare(board, row, i))) {
            return true;
        }
        i += 1;
    }

    i = col;
    while (i >= 0) {
        if ((pieceType != ' ' && existsPieceInSquare(board, row, i, pieceType, isWhite)) || (pieceType == ' ' && existsPieceInSquare(board, row, i))) {
            return true;
        }
        i -= 1;
    }

    return false;
}

bool existsPieceInVertical(ChessBoard& board, int row, int col, char pieceType = ' ', bool isWhite = true) {
    int i = row;

    while (i < 8) {
        if ((pieceType != ' ' && existsPieceInSquare(board, i, col, pieceType, isWhite)) || (pieceType == ' ' && existsPieceInSquare(board, i, col))) {
            return true;
        }
        i += 1;
    }

    i = row;
    while (i >= 0) {
        if ((pieceType != ' ' && existsPieceInSquare(board, i, col, pieceType, isWhite)) || (pieceType == ' ' && existsPieceInSquare(board, i, col))) {
            return true;
        }
        i -= 1;
    }

    return false;
}

bool existsPieceInDiagonal(ChessBoard& board, int row, int col, char pieceType = ' ', bool isWhite = true) {
    int i = row;
    int j = col;

    while (i < 8 && j < 8) {
        if ((pieceType != ' ' && existsPieceInSquare(board, i, j, pieceType, isWhite)) || (pieceType == ' ' && existsPieceInSquare(board, i, j))) {
            return true;
        }
        i += 1;
        j += 1;
    }

    i = row;
    j = col;
    while (i >= 0 && j >= 0) {
        if ((pieceType != ' ' && existsPieceInSquare(board, i, j, pieceType, isWhite)) || (pieceType == ' ' && existsPieceInSquare(board, i, j))) {
            return true;
        }
        i -= 1;
        j -= 1;
    }

    i = row;
    j = col;
    while (i < 8 && j >= 0) {
        if ((pieceType != ' ' && existsPieceInSquare(board, i, j, pieceType, isWhite)) || (pieceType == ' ' && existsPieceInSquare(board, i, j))) {
            return true;
        }
        i += 1;
        j -= 1;
    }

    i = row;
    j = col;
    while (i >= 0 && j < 8) {
        if ((pieceType != ' ' && existsPieceInSquare(board, i, j, pieceType, isWhite)) || (pieceType == ' ' && existsPieceInSquare(board, i, j))) {
            return true;
        }
        i -= 1;
        j += 1;
    }

    return false;
}

bool ChessBoard::checkIfPieceIsAttacked(Piece* piece, bool isWhite) {
    int row = piece->getRow();
    int col = piece->getCol();

    bool attackedByKing = existsPieceInSquare(*this, row+1, col+1, 'k', isWhite) || existsPieceInSquare(*this, row+1, col-1, 'k', isWhite) 
                        || existsPieceInSquare(*this, row-1, col+1, 'k', isWhite) || existsPieceInSquare(*this, row-1, col-1, 'k', isWhite) 
                        || existsPieceInSquare(*this, row+1, col, 'k', isWhite) || existsPieceInSquare(*this, row-1, col, 'k', isWhite) 
                        || existsPieceInSquare(*this, row, col+1, 'k', isWhite) || existsPieceInSquare(*this, row, col-1, 'k', isWhite);
    bool attackedByQueen = existsPieceInHorizontal(*this, row, col, 'q', isWhite) || existsPieceInVertical(*this, row, col, 'q', isWhite) || existsPieceInDiagonal(*this, row, col, 'q', isWhite);
    bool attackedByRook = existsPieceInHorizontal(*this, row, col, 'r', isWhite) || existsPieceInVertical(*this, row, col, 'r', isWhite);
    bool attackedByBishop = existsPieceInDiagonal(*this, row, col, 'b', isWhite);
    bool attackedByKnight = existsPieceInSquare(*this, row+2, col+1, 'n', isWhite) || existsPieceInSquare(*this, row+2, col-1, 'n', isWhite) 
                        || existsPieceInSquare(*this, row-2, col+1, 'n', isWhite) || existsPieceInSquare(*this, row-2, col-1, 'n', isWhite) 
                        || existsPieceInSquare(*this, row+1, col+2, 'n', isWhite) || existsPieceInSquare(*this, row+1, col-2, 'n', isWhite) 
                        || existsPieceInSquare(*this, row-1, col+2, 'n', isWhite) || existsPieceInSquare(*this, row-1, col-2, 'n', isWhite);
    bool attackedByPawn = isWhite ? existsPieceInSquare(*this, row+1, col+1, 'p', isWhite) || existsPieceInSquare(*this, row+1, col-1, 'p', isWhite) 
                        : existsPieceInSquare(*this, row-1, col+1, 'p', isWhite) || existsPieceInSquare(*this, row-1, col-1, 'p', isWhite);
    
    return attackedByKing || attackedByQueen || attackedByRook || attackedByBishop || attackedByKnight || attackedByPawn;
}

// check if king is in check 
// check if piece blocks check
// check if piece is king and moves away from check 
bool ChessBoard::checkIfKingIsInCheck(bool isWhite, int fromRow = -1, int fromCol = -1, int toRow = -1, int toCol = -1) {
    int kingRow, kingCol;
    Piece* king = getKing(isWhite);
    
    if (fromRow != -1) {
        ChessBoard boardAfterMove = ChessBoard{*this};
        boardAfterMove.movePiece(fromRow, fromCol, toRow, toCol);
        return boardAfterMove.checkIfPieceIsAttacked(king, king->getCol());
    }

    return checkIfPieceIsAttacked(king, king->getCol());
}

void ChessBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol, char promotionType = 'x') {
    Piece *p = getSquare(fromRow, fromCol);
    if (p == nullptr) { return; }

    // if (p->getPieceType() == 'k' && abs(fromCol - toCol) == 2) {
    //     if (toCol == 6) {
    //         movePiece(fromRow, 7, fromRow, 5);
    //     } else {
    //         movePiece(fromRow, 0, fromRow, 3);
    //     }
    // }

    // if (getSquare(toRow, toCol) != nullptr) {
    //     removePiece(toRow, toCol);
    // }

    // p->setCoords(toRow, toCol);
    // board[toRow][toCol] = p;
    // board[fromRow][fromCol] = nullptr;

    // if (p->getPieceType() == 'p' && (toRow == 0 || toRow == 7)) {
    //     placePiece(toRow, toCol, p->getIsWhite(), promotionType);
    // }

    p->setHasMoved(true);
    notifyObservers();
}

bool ChessBoard::verifyMove(int fromRow, int fromCol, int toRow, int toCol, bool isWhite, char promotionType) {
    if (fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7 || toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7) { return false; }

    Piece* piece = getSquare(fromRow, fromCol);
    if (piece == nullptr) { return false; }


    // check if a piece can move to the destination; no pieces block path; landing square is empty or occupied by DIFFERENT colour piece
    if (!(piece->checkValidMove(*this, toRow, toCol))) { return false; }

    // check that after the move, the king is not in check
    if (checkIfKingIsInCheck(isWhite, fromRow, fromCol, toRow, toCol)) { return false; }
    
    return true;
}

int ChessBoard::getNumKings(bool isWhite) {
    int numKings = 0;
    if (isWhite) {
        for (int i = 0; i < whitePieces.size(); ++i) {
            if (whitePieces[i].get()->getPieceType() == 'k') {
                numKings++;
            }
        }
    } else {
        for (int i = 0; i < blackPieces.size(); ++i) {
            if (blackPieces[i].get()->getPieceType() == 'k') {
                numKings++;
            }
        }
    }
    return numKings;
}

Piece* ChessBoard::getEnPassantPawn() {
    return enPassantPawn;
}
