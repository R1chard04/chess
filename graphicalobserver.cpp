#include "graphicalobserver.h"

GraphicalObserver::GraphicalObserver(ChessBoard* board) : mainSubject{board}, w{10 * 8, 10 * 8} {
    mainSubject->attach(this);
}

void GraphicalObserver::notify() {
    // 
    int square_size = 10; 
    int ctr = square_size / 2;
    int board_size = 8; 

    for(int i = 0; i < board_size; i++) {
        for(int j = 0; j < board_size; j++) {
            // 
            int cx = i * 10; 
            int cy = j * 10; 
            if((i + j) % 2 == 0) {
                // square is white
                w.fillRectangle(i, j, square_size, square_size, w.White);  
            } else {
                w.fillRectangle(i, j, square_size, square_size, w.Black);  
                // square is black
            }

            // if there is a piece, fill with piece label 
            Piece *currentPiece = mainSubject->getSquare(i, j);
            if(currentPiece != nullptr) {
                string s;
                if(currentPiece->getIsWhite()) {
                    s = {currentPiece->getPieceType()};
                } else {
                    s = {char(currentPiece->getPieceType() - 32)};
                }
                w.drawString(cx + ctr, cy + ctr, s);
            }
        }
    }
}

GraphicalObserver::~GraphicalObserver() { 
    if(mainSubject) mainSubject->detach(this);
}


