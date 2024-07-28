#include "chessboard.h"
#include "piece.h"
#include <iostream> 
#include <vector> 
using namespace std; 

Piece* ChessBoard::getSquare(int row, int col) {
    return board[row][col];
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