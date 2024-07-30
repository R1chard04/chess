#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <vector>
#include <memory>
#include "observer.h"
#include "textobserver.h"
#include "graphicalobserver.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
using namespace std;

class Observer;
class TextObserver;
class GraphicalObserver;

class ChessBoard {
    vector<Observer*> observers;
    vector<vector<Piece*>> board;

    vector<unique_ptr<Piece>> whitePieces;
    vector<unique_ptr<Piece>> blackPieces;

    Piece* enPassantPawn; // TODO: MAKE SURE TO UPDATE THIS WHEN A PAWN MOVES TWO SQUARES

    public:
        ChessBoard(TextObserver *textDisplay, GraphicalObserver *graphicsDisplay); 
        ChessBoard(const ChessBoard& other);
        virtual ~ChessBoard();

        void attach(Observer* o);
        void detach(Observer* o);
        void notifyObservers(); 

        bool checkIfPieceIsAttacked(Piece* piece, bool isWhite);
        bool verifyMove(int fromRow, int fromCol, int toRow, int toCol, bool isWhite, char promotionType = ' '); // ` ` represents no promotion

        bool checkIfKingIsInCheck(bool isWhite, int fromRow = -1, int fromCol = -1, int toRow = -1, int toCol = -1);
        bool checkCheckmate(bool isWhite); 
        bool checkStalemate(bool isWhite);

        Piece* getSquare(int row, int col) const;
        void removeAllPieces();
        void placePiece(int row, int col, bool isWhite, char pieceType, bool moved = false);
        void removePiece(int row, int col);
        void movePiece(int fromRow, int fromCol, int toRow, int toCol, char promotionType = 'x'); // uses verifyMove probably

        Piece* getKing(bool isWhite) const;
        int getNumKings(bool isWhite) const;
        Piece* getEnPassantPawn() const;
        void setEnPassantPawn(Piece*);
};

#endif
