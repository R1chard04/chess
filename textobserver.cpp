#include "textobserver.h"
using namespace std;

TextObserver::TextObserver() {
    // mainSubject->attach(this);
}

TextObserver::~TextObserver() {
    // mainSubject->detach(this);
}

void TextObserver::notify() {
    // cout << *mainSubject;
}

ostream &operator<<(ostream &out, const ChessBoard& board) {
  for (int i = 8; i >= 0; --i) {
    out << i << " ";
    for (int j = 0; j < 8; j++) {
      // Piece* p = board.getSquare(i, j);
      Piece* p = board.getSquare(i, j);
      if (p == nullptr) { out << " "; }
      else { out << p->getPieceType(); }
    }
    out << endl;
  }
  out << endl << "  abcdefgh" << endl;
  return out;
}
