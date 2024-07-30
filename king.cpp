#include "king.h"
#include "piece.h"
#include <climits>
#include <vector>
using namespace std; 

vector<vector<int>> kingMoves = {
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, 
    {1, 0}, {0, -1}, {0, 1}, {-1, 0}, 
    {-2, 0}, {2, 0}
};

King::King(bool isWhite, int row, int col): Piece{isWhite, kingMoves, 'k', row, col, INT_MAX} {}

bool King::checkValidMove(ChessBoard& board, int toRow, int toCol) {  
    
    int dy = toRow - row;
    int dx = toCol - col;   
    int board_size = 8;
    if (toRow < 0 || toRow >= board_size || toCol < 0 || toCol >= board_size) {
        return false; 
    }

    
    bool isKingMove = false; 
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i][0] == dx && moves[i][1] == dy) {
            isKingMove = true; 
            break; 
        }
    }   

    if (!isKingMove) { return false; }

    // check if moving to capture own piece
    if (board.getSquare(toRow, toCol) != nullptr && board.getSquare(toRow, toCol)->getIsWhite() == getIsWhite()) { return false; }

    // check if castling is valid
    if (dx == 2 || dx == -2) {
        // cout<<"castling under attempt"<<endl;
        if(board.getSquare(toRow, col + dx / 2) != nullptr) { return false; } 
        // cout<<"castling under attempt1"<<endl;
        if (this->getHasMoved()) { return false; }
        // cout<<"castling under attempt2"<<endl;
        Piece* rook = board.getSquare(this->row, dx == 2 ? 7 : 0);
        
        // for queen-side castles, check if there is a square on the right of the rook 
        if (dx == -2 && board.getSquare(row, 1) != nullptr) { return false; }

        if (rook == nullptr || rook->getPieceType() != 'r' || rook->getHasMoved()) { return false; }

        // cout<<"king castle passes all of these"<<endl;
        // check that king is not castling in or through check
        if (board.checkIfKingIsInCheck(this->getIsWhite())) { return false; }
        if (board.checkIfKingIsInCheck(this->getIsWhite(), this->row, this->col, toRow, col + dx / 2)) { return false; }
    }
    
    // check that king is not moving into check
    if (board.checkIfKingIsInCheck(this->getIsWhite(), this->row, this->col, toRow, toCol)) { return false; }

    return true; 
}
