#include "textobserver.h"
using namespace std;

TextObserver::TextObserver() {
    // mainSubject->attach(this);
}

TextObserver::~TextObserver() {
    // mainSubject->detach(this);
}

void TextObserver::notify(ChessBoard& board) {
    for (int i = 7; i >= 0; --i) {
      cout << i + 1 << " ";
      for (int j = 0; j <= 7; j++) {
        Piece* p = board.getSquare(i, j);
        if (p == nullptr) { cout << " "; }
        else { 
          if(p->getIsWhite()) {
            cout<<char(p->getPieceType() - 32);
          } else {
            cout<<p->getPieceType();
          }
        }
      }
      cout << endl;
    }
    cout << endl << "  abcdefgh" << endl;

}

ostream &operator<<(ostream &out, const TextObserver &textDisplay) {
  
}
