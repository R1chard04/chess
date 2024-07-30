#include "graphicalobserver.h"

const int margin = 40;
vector<string> xAxes = {"A", "B", "C", "D", "E", "F", "G", "H"};

GraphicalObserver::GraphicalObserver(Xwindow& w, int tileWidth): tileSize{600 / tileWidth}, window{w} {
    
    for (int i = 0; i < tileWidth; ++i) {
        window.drawString(i * tileSize + tileSize / 2 + margin, 600 + margin + margin / 2, xAxes[i]);
        window.drawString(margin / 2, i * tileSize + tileSize / 2 + margin, to_string(8 - i));
        vector<char> emptyRow;
        for (int j = 0; j < tileWidth; ++j) {;
            emptyRow.push_back(' ');
            window.fillRectangle(j * tileSize + margin, i * tileSize + margin, tileSize, tileSize, (i + j) % 2 == 1 ? window.Green : window.White);
        }
        
        boardState.push_back(emptyRow);
    }
}

void GraphicalObserver::notify(ChessBoard& board) {

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* p = board.getSquare(7-i, j);

            if ((p == nullptr && boardState.at(7-i).at(j) == ' ') || (p != nullptr && (p->getPieceType() == boardState.at(7-i).at(j)))) { continue; }
            else { 
                if (p == nullptr) { boardState.at(7-i).at(j) = ' '; }
                else {
                    boardState.at(7-i).at(j) = (p->getIsWhite()) ? p->getPieceType() - 32 : p->getPieceType();
                }
                // boardState.at(7-i).at(j) = (p == nullptr) ? ' ' : p->getPieceType(); 
            }

            window.fillRectangle(j * tileSize + margin, i * tileSize + margin, tileSize, tileSize, (i + j) % 2 == 1 ? window.Green : window.White);
            
            if (p != nullptr) {
                char pieceType = p->getIsWhite() ? p->getPieceType() - 32 : p->getPieceType();
                string pieceTypeStr {pieceType};
                window.drawString(j * tileSize + tileSize / 2 - tileSize / 10 + margin, i * tileSize + tileSize / 2 + margin, pieceTypeStr);
            }
        }
    }
}

GraphicalObserver::~GraphicalObserver() {}


