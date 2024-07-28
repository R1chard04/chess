#include "knight.h"
#include "piece.h"
#include <vector>
using namespace std; 

vector<vector<int>> knightMoves = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {-1, 2}, {1, -2}, {-1, -2},
};

Knight::Knight(string pieceColour): Piece{pieceColour, knightMoves, 'n'} {}
