#include "bishop.h"
#include "piece.h"
#include <vector>
using namespace std; 

vector<vector<int>> bishopMoves = {
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, 
    {2, 2}, {2, -2}, {-2, 2}, {-2, -2},
    {3, 3}, {3, -3}, {-3, 3}, {-3, -3},
    {4, 4}, {4, -4}, {-4, 4}, {-4, -4},
    {5, 5}, {5, -5}, {-5, 5}, {-5, -5},
    {6, 6}, {6, -6}, {-6, 6}, {-6, -6},
    {7, 7}, {7, -7}, {-7, 7}, {-7, -7},
    {8, 8}, {8, -8}, {-8, 8}, {-8, -8},
};

Bishop::Bishop(string pieceColour, int row, int col): Piece{pieceColour, bishopMoves, 'b', row, col} {}

bool Bishop::checkValidMove(ChessBoard& cBoard, int toRow, int toCol) {
    int board_size = 8;
    if(toRow < 0 || toRow >= board_size || toCol < 0 || toCol >= board_size) {
        return false; 
    }
    
    if (toRow == row && toCol == col) { return false; }
    if (abs(toRow - row) != abs(toCol - col)) { return false; }
    for (int i = 1; i < abs(toRow - row) - 1; ++i) {
        Piece* p = cBoard.getSquare(toRow > row ? row + i : row - i, toCol > col ? col + i: col - i);
        if (p != nullptr) { return false; }
    }
    Piece* p = cBoard.getSquare(toRow, toCol);
    if (p != nullptr && p->getColour() == this->getColour()) { return false; }

    return true;
}
