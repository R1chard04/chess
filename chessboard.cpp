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

Piece* ChessBoard::getSquare(int row, int col) {
    return board[row][col];
}

void ChessBoard::removePiece(int row, int col) {
    Piece *p = getSquare(row, col);
    if (p == nullptr) {
        return;
    }

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

    removePiece(row, col);
    if (isWhite) {
        whitePieces.push_back(move(p));
    } else {
        blackPieces.push_back(move(p));
    }
}

// bool ChessBoard::verifyMove(int fromRow, int fromCol, int toRow, int toCol, string colour, char promotionType) {
//     if(fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7 || toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7) {
//         return false;
//     }

//     int dx = toCol - fromCol;
//     int dy = toRow - fromRow;

//     Piece *piece = board[fromRow][fromCol];

//     // check if the piece is in the set of moves the piece can make
//     if(piece->isInValidMoves(dx, dy) == false) {
//         return false;
//     }

//     // special conditions: knights and pawns, king castle 
//     if(piece->getPieceType() == 'p') {

//     } else if(piece->getPieceType() == 'n') {
//         // check if 
//     } else {
//         // check if there is a piece blocking the path 
//         dx == 8 dy == 8
//         for(int i = 0; i < )
//     }

//     // check if the piece is currently pinned 
//     if()

//     // check if king is in check 
//         // check if piece blocks check
//         // check if piece is king and moves away from check 


// }