#include "knight.h"
#include "piece.h"
#include <vector>
using namespace std; 

vector<vector<int>> knightMoves = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {-1, 2}, {1, -2}, {-1, -2},
};

Knight::Knight(string pieceColour, int row, int col): Piece{pieceColour, knightMoves, 'n', row, col} {}


bool Knight::checkValidMove(ChessBoard& board, int toRow, int toCol) {  
    int dy = toRow - row;
    int dx = toCol - col;
    int board_size = 8;
    if(toRow < 0 || toRow >= board_size || toCol < 0 || toCol >= board_size) {
        return false; 
    }

    bool isKnightMove = false; 
    for(int i = 0; i < moves.size(); i++) {
        if(moves[i][0] == dx && moves[i][1] == dy) {
            isKnightMove = true; 
            break; 
        }
    }

    if(!isKnightMove) {
        return false; 
    }

    // check if moving to capture own piece
    if(board.getSquare(toRow, toCol)->getColour() == getColour()) {
        return false; 
    }

    return true; 
}