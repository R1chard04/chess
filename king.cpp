#include "king.h"
#include "piece.h"
#include <vector>
using namespace std; 


King::King(string pieceColour): Piece(pieceColour) {
    moves = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, 
            {1, 0}, {0, -1}, {0, 1}, {-1, 0}, 
    };
}