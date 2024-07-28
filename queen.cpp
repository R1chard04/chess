#include "queen.h"
#include "piece.h"
#include <vector>
using namespace std; 

vector<vector<int>> queenMoves = {
    // horizontal moves
    {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0},
    {-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}, {-8, 0},
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8},
    {0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}, {0, -8},

    // diagonal moves
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, 
    {2, 2}, {2, -2}, {-2, 2}, {-2, -2},
    {3, 3}, {3, -3}, {-3, 3}, {-3, -3},
    {4, 4}, {4, -4}, {-4, 4}, {-4, -4},
    {5, 5}, {5, -5}, {-5, 5}, {-5, -5},
    {6, 6}, {6, -6}, {-6, 6}, {-6, -6},
    {7, 7}, {7, -7}, {-7, 7}, {-7, -7},
    {8, 8}, {8, -8}, {-8, 8}, {-8, -8}
};

Queen::Queen(string pieceColour, int row, int col): Piece{pieceColour, queenMoves, 'q', row, col} {}

bool Queen::checkValidMove(ChessBoard& cBoard, int toRow, int toCol) {
    if (!(toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)) { return false; }
    if (toRow == row && toCol == col) { return false; }
    
    if ((toRow == row || toCol == col) && !(toRow == row && toCol == col)) {
        if (toRow == row) {
            for (int i = 0; i < abs(toCol - col) - 1; ++i) {
                Piece* p = cBoard.getSquare(row, toCol > col ? col + i : col - i);
                if (p != nullptr) { return false; }
            }
        } else if (toCol == col) {
            for (int i = 0; i < abs(toRow - row) - 1; ++i) {
                Piece* p = cBoard.getSquare(toRow > row ? row + i : row - i, col);
                if (p != nullptr) { return false; }
            }
        }
    } else if (abs(toRow - row) == abs(toCol - col)) {
        for (int i = 1; i < abs(toRow - row) - 1; ++i) {
            Piece* p = cBoard.getSquare(toRow > row ? row + i : row - i, toCol > col ? col + i: col - i);
            if (p != nullptr) { return false; }
        }
    } else {
        return false;
    }

    Piece* p = cBoard.getSquare(toRow, toCol);
    if (p != nullptr && p->getColour() == this->getColour()) { return false; }

    return true;
}
