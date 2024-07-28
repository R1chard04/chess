#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include <vector>
#include <string> 
#include "observer.h"
#include "chessboard.h"
#include "piece.h"
using namespace std;

class TextObserver : public Observer {
    ChessBoard* mainSubject; 
    
    public:
        TextObserver();
        ~TextObserver();

        void notify() override;


        friend ostream &operator<<(ostream &out, const ChessBoard &board);
};
#endif
