#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <vector>
#include "observer.h"
using namespace std;

class Observer;
class Piece;
class ChessBoard {
    vector<Observer*> observers;
    vector<vector<Piece*>> board;


    public:
        ChessBoard(); 
        virtual ~ChessBoard();

        void attach(Observer* o);
        void detach(Observer* o);
        void notifyObservers(); 
        char getState(); // needs further refining

        bool verifyMove(int fromRow, int fromCol, int toRow, int toCol, char promotionType = 'x'); // `x` represents no promotion

        bool checkCheckMate(); 

        bool getIfRookMoved(string colour);  // needs further refining
        bool getIfKingMoved(string colour);  // needs further refining

        Piece *getSquare(int row, int col);

        // richard added this!!!!
        void removeAllPieces();
        void placePiece(int row, int col, bool isWhite, char pieceType);
        void removePiece(int row, int col);
        Piece* getPiece(int row, int col) const;
        void movePiece(int fromRow, int fromCol, int toRow, int toCol, char promotionType = 'x'); // uses verifyMove probably
};

#endif
