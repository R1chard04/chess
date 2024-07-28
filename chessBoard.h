#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
using namespace std;

class Observer;

class ChessBoard {
    vector<Observer*> observers;
    vector<vector<Piece*>> board;

    vector<unique_ptr<Piece>> whitePieces;
    vector<unique_ptr<Piece>> blackPieces;

    public:
        ChessBoard(); 
        virtual ~ChessBoard();

        void attach(Observer* o);
        void detach(Observer* o);
        void notifyObservers(); 
        char getState(); // needs further refining

        bool verifyMove(int fromRow, int fromCol, int toRow, int toCol, char promotionType = 'x'); // `x` represents no promotion

        bool checkCheck(string colour);
        bool checkCheckmate(); 
        bool checkStalemate(string colour);

        bool getIfRookMoved(string colour);  // needs further refining
        bool getIfKingMoved(string colour);  // needs further refining

        Piece *getSquare(int row, int col);

        // richard added this!!!!
        void removeAllPieces();
        void placePiece(int row, int col, bool isWhite, char pieceType, bool moved = false);
        void removePiece(int row, int col);
        void movePiece(int fromRow, int fromCol, int toRow, int toCol, char promotionType = 'x'); // uses verifyMove probably
};

#endif
