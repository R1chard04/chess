#include "knight.h"
#include "piece.h"
#include <vector>
using namespace std; 


Knight::Knight(string pieceColour): Piece(pieceColour) {
    moves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {-1, 2}, {1, -2}, {-1, -2},
    };
}