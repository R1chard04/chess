#include "king.h"
#include "piece.h"
#include <vector>
using namespace std; 

vector<vector<int>> kingMoves = {
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, 
    {1, 0}, {0, -1}, {0, 1}, {-1, 0}, 
};

King::King(string pieceColour): Piece{pieceColour, kingMoves, 'k'} {}
