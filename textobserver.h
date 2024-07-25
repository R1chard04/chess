#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include <vector>
#include <string> 
#include "observer.h"
#include "chessBoard.h"
using namespace std;

class TextObserver : public Observer {
    ChessBoard* mainSubject; 
    
    public:
        TextObserver(ChessBoard* board);

        void notify() override;

        ~TextObserver();
};
#endif
