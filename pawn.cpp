#include "pawn.h"
#include "piece.h"
#include <vector>
using namespace std; 

vector<vector<int>> blackPawnMoves = {
    {0, 1}, {1, 1}, {-1, 1}, {0, 2}
};

vector<vector<int>> whitePawnMoves = {
    {0, -1}, {1, -1}, {-1, -1}, {0, -2}
};

Pawn::Pawn(string pieceColour): Piece{pieceColour, pieceColour == "white" ? whitePawnMoves : blackPawnMoves, 'p'} {}
