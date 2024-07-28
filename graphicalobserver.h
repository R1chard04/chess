#ifndef GRAPHICALOBSERVER_H
#define GRAPHICALOBSERVER_H
#include <vector>
#include <string> 
#include "window.h"
#include "observer.h"
#include "chessboard.h"
using namespace std;

class ChessBoard;

class GraphicalObserver : public Observer {
    ChessBoard* mainSubject; 

    Xwindow w; 
    
    public:
        GraphicalObserver(ChessBoard* mainSubject);

        void notify(ChessBoard& board) override;

        ~GraphicalObserver();
};
#endif
