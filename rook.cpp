#include "rook.h"
#include "piece.h"
#include <vector>
using namespace std; 

vector<vector<int>> rookMoves = {
    {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0},
    {-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}, {-8, 0},
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8},
    {0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}, {0, -8}
};

Rook::Rook(bool isWhite, int row, int col): Piece{isWhite, rookMoves, 'r', row, col, 5} {}

bool Rook::checkValidMove(ChessBoard& cBoard, int toRow, int toCol) {
    int board_size = 8;
    if(toRow < 0 || toRow >= board_size || toCol < 0 || toCol >= board_size) {
        return false; 
    }
    
    if ((toRow != row && toCol != col) || (toRow == row && toCol == col)) { return false; }
    
    if (toRow == row) {
        for (int i = 1; i <= abs(toCol - col) - 1; ++i) {
            Piece* p = cBoard.getSquare(row, toCol > col ? col + i : col - i);
            if (p != nullptr) { return false; }
        }
    } else if (toCol == col) {
        for (int i = 1; i <= abs(toRow - row) - 1; ++i) {
            Piece* p = cBoard.getSquare(toRow > row ? row + i : row - i, col);
            if (p != nullptr) { return false; }
        }
    }
    Piece* p = cBoard.getSquare(toRow, toCol);
    if (p != nullptr && p->getIsWhite() == this->getIsWhite()) { return false; }

    return true;
}
