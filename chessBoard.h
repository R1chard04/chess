#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <vector>
#include "observer.h"
using namespace std;

class Observer;
class ChessBoard {
    vector<Observer*> observers;
    vector<vector<char>> board;


    public:
        ChessBoard(); 

        void attach(Observer* o);
        void detach(Observer* o);
        void notifyObservers(); 
        char getState(); // needs further refining

        bool verifyMove(string fromSquare, string toSquare);

        bool checkCheckMate(); 

        bool getIfRookMoved(string colour);  // needs further refining
        bool getIfKingMoved(string colour);  // needs further refining

        virtual ~ChessBoard();



};

#endif
