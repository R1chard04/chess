#include "graphicalobserver.h"

const int margin = 40;
vector<string> xAxes = {"A", "B", "C", "D", "E", "F", "G", "H"};

GraphicalObserver::GraphicalObserver(Xwindow& w, int tileWidth): tileSize{600 / tileWidth}, window{w} {
    
    for (int i = 0; i < tileWidth; ++i) {
        window.drawString(i * tileSize + tileSize / 2 + margin, 600 + margin + margin / 2, xAxes[i]);
        window.drawString(margin / 2, i * tileSize + tileSize / 2 + margin, to_string(8 - i));
        for (int j = 0; j < tileWidth; ++j) {
            window.fillRectangle(j * tileSize + margin, i * tileSize + margin, tileSize, tileSize, (i + j) % 2 == 1 ? window.Green : window.White);
        }
    }
}

void GraphicalObserver::notify(ChessBoard& board) {

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            window.fillRectangle(j * tileSize + margin, i * tileSize + margin, tileSize, tileSize, (i + j) % 2 == 1 ? window.Green : window.White);
            Piece* p = board.getSquare(7-i, j);
            if (p != nullptr) {
                char pieceType = p->getIsWhite() ? p->getPieceType() - 32 : p->getPieceType();
                string pieceTypeStr {pieceType};
                window.drawString(j * tileSize + tileSize / 2 - tileSize / 10 + margin, i * tileSize + tileSize / 2 + margin, pieceTypeStr);
            }
        }
    }
    // 
    // int square_size = 10; 
    // int ctr = square_size / 2;
    // int board_size = 8; 

    // for(int i = 0; i < board_size; i++) {
    //     for(int j = 0; j < board_size; j++) {
    //         // 
    //         int cx = i * 10; 
    //         int cy = j * 10; 
    //         if((i + j) % 2 == 0) {
    //             // square is white
    //             window.fillRectangle(i, j, square_size, square_size, window.White);  
    //         } else {
    //             window.fillRectangle(i, j, square_size, square_size, window.Black);  
    //             // square is black
    //         }

    //         // if there is a piece, fill with piece label 
    //         Piece *currentPiece = board.getSquare(i, j);
    //         if(currentPiece != nullptr) {
    //             string s;
    //             if(currentPiece->getIsWhite()) {
    //                 s = {currentPiece->getPieceType()};
    //             } else {
    //                 s = {char(currentPiece->getPieceType() - 32)};
    //             }
    //             window.drawString(cx + ctr, cy + ctr, s);
    //         }
    //     }
    // }
}

GraphicalObserver::~GraphicalObserver() {}


