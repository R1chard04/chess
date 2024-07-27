#include "pawn.h"
#include "piece.h"
#include <vector>
using namespace std; 


Pawn::Pawn(string pieceColour): Piece(pieceColour) {
    if(pieceColour == "black") {
        moves = {
            {0, 1}, {1, 1}, {-1, 1} // 1, 1  and -1, 1 is for captures only
        };
    } else {
        moves = {
            {0, -1}, {1, -1}, {-1, -1} // 1, -1 and -1, -1 is for captures only
        };   // 
    }
}