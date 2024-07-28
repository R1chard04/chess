#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <vector>
#include <memory>
#include "observer.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
using namespace std;

class Observer;

class ChessBoard {
    vector<Observer*> observers;
    vector<vector<Piece*>> board;

    vector<unique_ptr<Piece>> whitePieces;
    vector<unique_ptr<Piece>> blackPieces;

    Piece* enPassantPawn; // TODO: MAKE SURE TO UPDATE THIS WHEN A PAWN MOVES TWO SQUARES

    public:
        ChessBoard(); 
        ChessBoard(const ChessBoard& other);
        virtual ~ChessBoard();

        void attach(Observer* o);
        void detach(Observer* o);
        void notifyObservers(); 
        // char getState(); // needs further refining

        bool checkIfPieceIsAttacked(Piece* piece, bool isWhite);
        bool verifyMove(int fromRow, int fromCol, int toRow, int toCol, bool isWhite, char promotionType = ' '); // ` ` represents no promotion

        bool checkIfKingIsInCheck(bool isWhite, int fromRow = -1, int fromCol = -1, int toRow = -1, int toCol = -1);
        bool checkCheckmate(); 
        bool checkStalemate(bool isWhite);

        bool getIfRookMoved(string colour);  // needs further refining
        bool getIfKingMoved(bool isWhite);  // needs further refining

        Piece *getSquare(int row, int col);
        void removeAllPieces();
        void placePiece(int row, int col, bool isWhite, char pieceType, bool moved = false);
        void removePiece(int row, int col);
        void movePiece(int fromRow, int fromCol, int toRow, int toCol, char promotionType = 'x'); // uses verifyMove probably

        Piece* getKing(bool isWhite);
        int getNumKings(bool isWhite);
        Piece* getEnPassantPawn();
};

#endif
