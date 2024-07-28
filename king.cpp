#include "king.h"
#include "piece.h"
#include <vector>
using namespace std; 

vector<vector<int>> kingMoves = {
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, 
    {1, 0}, {0, -1}, {0, 1}, {-1, 0}, 
    {-2, 0}, {2, 0}
};

King::King(string pieceColour, int row, int col): Piece{pieceColour, kingMoves, 'k', row, col} {}

bool King::checkValidMove(ChessBoard& board, int toRow, int toCol) {  
    int dy = toRow - row;
    int dx = toCol - col;   
    int board_size = 8;
    if(toRow < 0 || toRow >= board_size || toCol < 0 || toCol >= board_size) {
        return false; 
    }

    bool isKingMove = false; 
    for(int i = 0; i < moves.size(); i++) {
        if(moves[i][0] == dx && moves[i][1] == dy) {
            isKingMove = true; 
            break; 
        }
    }   

    if(!isKingMove) {
        return false; 
    }

    // check if moving to capture own piece
    if(board.getSquare(toRow, toCol)->getColour() == getColour()) {
        return false; 
    }

    if(dx == 2 || dx == -2) {
        if(board.getSquare(toRow, toCol + dx / 2) != nullptr) {
            return false; 
        }   
    }

    return true; 
}