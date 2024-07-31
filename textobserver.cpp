#include "textobserver.h"
using namespace std;

TextObserver::TextObserver() {}

TextObserver::~TextObserver() {}

void TextObserver::notify(ChessBoard& board) {
    for (int i = 7; i >= 0; --i) {
      cout << i + 1 << " ";
      for (int j = 0; j <= 7; j++) {
        Piece* p = board.getSquare(i, j);
        if (p == nullptr) { 
          if ((i + j) % 2 == 0) { // a dark square is marked in a tile when the sum of the x and y axes is even
            cout << "_";
          } else {
            cout << " ";
          } 
        }
        else { 
          if(p->getIsWhite()) {
            cout << char(p->getPieceType() - 32);
          } else {
            cout << p->getPieceType();
          }
        }
      }
      cout << endl;
    }
    cout << endl << "  abcdefgh" << endl;
}
