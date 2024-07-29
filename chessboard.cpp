#include "chessboard.h"
#include "piece.h"
#include <iostream> 
#include <vector> 
#include <cassert>
using namespace std; 

ChessBoard::ChessBoard(TextObserver* textDisplay, GraphicalObserver* graphicsDisplay) {
    for (int i = 0; i < 8; ++i) {
        vector<Piece*> row {8, nullptr};
        board.push_back(row);
    }
    if (textDisplay != nullptr) attach(textDisplay);
    if (graphicsDisplay != nullptr) attach(graphicsDisplay);
}

ChessBoard::ChessBoard(const ChessBoard& other) {
    for (int i = 0; i < 8; ++i) {
        vector<Piece*> row {8, nullptr};
        board.push_back(row);
    }
    for (int i = 0; i < other.whitePieces.size(); ++i) {
        Piece* p = other.whitePieces[i].get();
        placePiece(p->getRow(), p->getCol(), p->getIsWhite(), p->getPieceType(), p->getHasMoved());
    }
    for (int i = 0; i < other.blackPieces.size(); ++i) {
        Piece* p = other.blackPieces[i].get();
        placePiece(p->getRow(), p->getCol(), p->getIsWhite(), p->getPieceType(), p->getHasMoved());
    }
}

ChessBoard::~ChessBoard() {}

void ChessBoard::attach(Observer* o) {
    observers.emplace_back(o);
}

void ChessBoard::detach(Observer* o) {
    for (int i = 0; i < observers.size(); ++i) {
        if (observers[i] == o) {
            observers.erase(observers.begin() + i);
            break;
        }
    }
}

void ChessBoard::notifyObservers() {
    cout << "size: " << observers.size() << endl;
    for (int i = 0; i < observers.size(); ++i) {
        observers[i]->notify(*this);
        cout << "i: " << i << endl;
    }
}

Piece* ChessBoard::getSquare(int row, int col) const {
    return board[row][col];
}

void ChessBoard::removePiece(int row, int col) {
    Piece *p = getSquare(row, col);
    if (p == nullptr) { return; }

    if (p->getIsWhite()) {
        for (int i = 0; i < whitePieces.size(); ++i) {
            if (whitePieces[i].get() == p) {
                whitePieces.erase(whitePieces.begin() + i);
                break;
            }
        }
    } else {
        for (int i = 0; i < blackPieces.size(); ++i) {
            if (blackPieces[i].get() == p) {
                blackPieces.erase(blackPieces.begin() + i);
                break;
            }
        }
    }

    board[row][col] = nullptr;
}

void ChessBoard::placePiece(int row, int col, bool isWhite, char pieceType, bool moved) {
    if (getSquare(row, col) != nullptr) {
        removePiece(row, col);
    }

    unique_ptr<Piece> p;
    if (pieceType == 'p') { p = make_unique<Pawn>(isWhite, row, col); } 
    else if (pieceType == 'r') { p = make_unique<Rook>(isWhite, row, col); } 
    else if (pieceType == 'n') { p = make_unique<Knight>(isWhite, row, col); } 
    else if (pieceType == 'b') { p = make_unique<Bishop>(isWhite, row, col); } 
    else if (pieceType == 'q') { p = make_unique<Queen>(isWhite, row, col); } 
    else if (pieceType == 'k') { p = make_unique<King>(isWhite, row, col); }

    p.get()->setHasMoved(moved);
    board[row][col] = p.get();
    notifyObservers();
    if (isWhite) {
        whitePieces.emplace_back(move(p));
    } else {
        blackPieces.emplace_back(move(p));
    }
}

void ChessBoard::removeAllPieces() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            removePiece(i, j);
        }
    }
}

Piece* ChessBoard::getKing(bool isWhite) const {
    if (isWhite) {
        for (int i = 0; i < whitePieces.size(); ++i) {
            if (whitePieces[i].get()->getPieceType() == 'k') {
                return whitePieces[i].get();
            }
        }
    } else {
        for (int i = 0; i < blackPieces.size(); ++i) {
            if (blackPieces[i].get()->getPieceType() == 'k') {
                return blackPieces[i].get();
            }
        }
    }
    return nullptr;
}

void printBoard(ChessBoard& board) {
    for(int i = 7; i >= 0; i--) {
        for(int j = 0; j < 8; j++) {
            if(board.getSquare(i, j) != nullptr) {
                cout<<board.getSquare(i, j)->getPieceType(); 
            } else {
                cout<<" ";
            }
        } cout<<endl; 
    }
}

bool existsPieceInSquare(ChessBoard& board, int row, int col, char pieceType = ' ', bool isWhite = true) {
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;
    if (pieceType == ' ') {
        return board.getSquare(row, col) != nullptr;
    }
    Piece* tmpPiece = board.getSquare(row, col);
    return (tmpPiece != nullptr && tmpPiece->getPieceType() == pieceType && tmpPiece->getIsWhite() != isWhite);
}

bool existsPieceInHorizontal(ChessBoard& board, int row, int col, char pieceType = ' ', bool isWhite = true) {
    int i = col;

    while (i < 8) {
        if (existsPieceInSquare(board, row, i)) {
            if (pieceType != ' ' && existsPieceInSquare(board, row, i, pieceType, isWhite)) {
                return true;
            } else if(i != col) {
                break;
            }
        }
        i += 1;
    }

    i = col;
    while (i >= 0) {
        if (existsPieceInSquare(board, row, i)) {
            if (pieceType != ' ' && existsPieceInSquare(board, row, i, pieceType, isWhite)) {
                return true;
            } else if(i != col) {
                break;
            }
        }
        i -= 1;
    }

    return false;
}

bool existsPieceInVertical(ChessBoard& board, int row, int col, char pieceType = ' ', bool isWhite = true) {
    int i = row;

    while (i < 8) {
        if (existsPieceInSquare(board, i, col)) {
            if (pieceType != ' ' && existsPieceInSquare(board, i, col, pieceType, isWhite)) {
                return true;
            } else if(i != row) {
                break;
            }
        }
        i += 1;
    }

    i = row;
    while (i >= 0) {
        if (existsPieceInSquare(board, i, col)) {
            if (pieceType != ' ' && existsPieceInSquare(board, i, col, pieceType, isWhite)) {
                return true;
            } else if(i != row) {
                break;
            }
        }
        i -= 1;
    }

    return false;
}

bool existsPieceInDiagonal(ChessBoard& board, int row, int col, char pieceType = ' ', bool isWhite = true) {
    int i = row;
    int j = col;

    while (i < 8 && j < 8) {
        if (existsPieceInSquare(board, i, j)) {
            if (pieceType != ' ' && existsPieceInSquare(board, i, j, pieceType, isWhite)) {
                return true;
            } else if(i != row || j != col) {
                break;
            }
        }
        i += 1;
        j += 1;
    }
    // 6, 5
    i = row;
    j = col;
    while (i >= 0 && j >= 0) {
        if (existsPieceInSquare(board, i, j)) {
            if (pieceType != ' ' && existsPieceInSquare(board, i, j, pieceType, isWhite)) {
                return true;
            } else if(i != row || j != col) {
                break;
            }
        }
        i -= 1;
        j -= 1;
    }

    i = row;
    j = col;
    while (i < 8 && j >= 0) {
        if (existsPieceInSquare(board, i, j)) {
            if (pieceType != ' ' && existsPieceInSquare(board, i, j, pieceType, isWhite)) {
                return true;
            } else if(i != row || j != col) {
                break;
            }
        }
        i += 1;
        j -= 1;
    }

    i = row;
    j = col;
    while (i >= 0 && j < 8) {
        if (existsPieceInSquare(board, i, j)) {
            if (pieceType != ' ' && existsPieceInSquare(board, i, j, pieceType, isWhite)) {
                return true;
            } else if(i != row || j != col) {
                break;
            }
        }
        i -= 1;
        j += 1;
    }

    return false;
}

bool ChessBoard::checkIfPieceIsAttacked(Piece* piece, bool isWhite) {
    int row = piece->getRow();
    int col = piece->getCol();
    
    cout<<row<<" "<<col<<" "<<endl; 
    bool attackedByKing = existsPieceInSquare(*this, row+1, col+1, 'k', isWhite) || existsPieceInSquare(*this, row+1, col-1, 'k', isWhite) 
                        || existsPieceInSquare(*this, row-1, col+1, 'k', isWhite) || existsPieceInSquare(*this, row-1, col-1, 'k', isWhite) 
                        || existsPieceInSquare(*this, row+1, col, 'k', isWhite) || existsPieceInSquare(*this, row-1, col, 'k', isWhite) 
                        || existsPieceInSquare(*this, row, col+1, 'k', isWhite) || existsPieceInSquare(*this, row, col-1, 'k', isWhite);
    cout << "attacked: " << attackedByKing << endl;
    bool attackedByQueen = existsPieceInHorizontal(*this, row, col, 'q', isWhite) || existsPieceInVertical(*this, row, col, 'q', isWhite) || existsPieceInDiagonal(*this, row, col, 'q', isWhite);
    cout << "attacked: " << attackedByQueen << endl;
    bool attackedByRook = existsPieceInHorizontal(*this, row, col, 'r', isWhite) || existsPieceInVertical(*this, row, col, 'r', isWhite);
    cout << "attacked: " << attackedByRook << endl;
    bool attackedByBishop = existsPieceInDiagonal(*this, row, col, 'b', isWhite);
    cout << "attacked: " << attackedByBishop << endl;
    bool attackedByKnight = existsPieceInSquare(*this, row+2, col+1, 'n', isWhite) || existsPieceInSquare(*this, row+2, col-1, 'n', isWhite)
                        || existsPieceInSquare(*this, row-2, col+1, 'n', isWhite) || existsPieceInSquare(*this, row-2, col-1, 'n', isWhite) 
                        || existsPieceInSquare(*this, row+1, col+2, 'n', isWhite) || existsPieceInSquare(*this, row+1, col-2, 'n', isWhite) 
                        || existsPieceInSquare(*this, row-1, col+2, 'n', isWhite) || existsPieceInSquare(*this, row-1, col-2, 'n', isWhite);
    cout << "attacked: " << attackedByKnight << endl;
    bool attackedByPawn = isWhite ? existsPieceInSquare(*this, row-1, col-1, 'p', isWhite) || existsPieceInSquare(*this, row-1, col+1, 'p', isWhite) || (piece->getPieceType() == 'p' && enPassantPawn != nullptr && (getSquare(row, col-1) == enPassantPawn || getSquare(row, col+1) == enPassantPawn))
                        : existsPieceInSquare(*this, row+1, col-1, 'p', isWhite) || existsPieceInSquare(*this, row+1, col+1, 'p', isWhite) || (piece->getPieceType() == 'p' && enPassantPawn != nullptr && (getSquare(row, col-1) == enPassantPawn || getSquare(row, col+1) == enPassantPawn));
    cout << "attacked: " << attackedByPawn << endl;
    return attackedByKing || attackedByQueen || attackedByRook || attackedByBishop || attackedByKnight || attackedByPawn;
}

// check if king is in check 
// check if piece blocks check
// check if piece is king and moves away from check 
bool ChessBoard::checkIfKingIsInCheck(bool isWhite, int fromRow, int fromCol, int toRow, int toCol) {
    int kingRow, kingCol;
    Piece* king = getKing(isWhite);
    
    if (fromRow != -1) {
        ChessBoard boardAfterMove = ChessBoard{*this};
        cout << "copy contructing done" << endl;
        boardAfterMove.movePiece(fromRow, fromCol, toRow, toCol);
        cout << "piece is moved from" <<fromRow<<" "<<fromCol<<" to" << " "<< toRow << " " <<toCol<<endl;
        printBoard(boardAfterMove); 
        cout<<"if output breaks here this means that the piece was not moved correctly in checkIfKingIsInCheck"<<endl;
        Piece *newKing = boardAfterMove.getKing(isWhite); 
        assert(newKing != nullptr); 
        return boardAfterMove.checkIfPieceIsAttacked(newKing, king->getIsWhite());
    }

    return checkIfPieceIsAttacked(king, king->getCol());
}

vector<vector<int>> generateMoves(ChessBoard& cBoard, bool isWhite) {
    int board_size = 8; 
    vector<vector<int> > res; 

    for(int i = 0; i < board_size; i++) {
        for(int j = 0; j < board_size; j++) {
            // piece is nullptr
            if(cBoard.getSquare(i, j) == nullptr);
            
            // piece is not our colour
            if(cBoard.getSquare(i, j)->getIsWhite() != isWhite) continue; 

            // square is our piece 
            for(int k = 0; k < board_size; k++) {
                for(int h = 0; h < board_size; h++) {
                    if(cBoard.verifyMove(i, j, k, h, isWhite)) {
                        // valid move
                        res.push_back({i, j, k, h});
                    }
                }
            }
        }
    }
    return res; 
}

bool ChessBoard::checkCheckmate(bool isWhite) {
    vector<vector<int>> moves = generateMoves(*this, isWhite);
    if(moves.size() == 0) return true; 
    return false;     
}

bool ChessBoard::checkStalemate() {
    return checkCheckmate(true) && checkCheckmate(false);
}

void ChessBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol, char promotionType) {
    Piece *p = getSquare(fromRow, fromCol);
    if (p == nullptr) { return; }

    // set en passant pawn
    if (p->getPieceType() == 'p' && abs(toRow - p->getRow()) == 2) {
        enPassantPawn = p;
    } else {
        enPassantPawn = nullptr;
    }

    // moving rook for castling
    if (p->getPieceType() == 'k' && abs(fromCol - toCol) == 2) {
        if (toCol == 6) {
            movePiece(fromRow, 7, fromRow, 5);
        } else {
            movePiece(fromRow, 0, fromRow, 3);
        }
    }

    // remove en passant pawn if it exists
    if (p->getPieceType() == 'p' && abs(toRow - p->getRow()) == abs(toCol - p->getCol()) && getSquare(toRow, toCol) == nullptr) {
        removePiece(p->getRow(), toCol);
    }

    if (getSquare(toRow, toCol) != nullptr) {
        removePiece(toRow, toCol);
    }
    p->setCoords(toRow, toCol);
    board[toRow][toCol] = p;
    board[fromRow][fromCol] = nullptr;

    // pawn promotion
    if (p->getPieceType() == 'p' && (toRow == 0 || toRow == 7)) { // TODO: check if this works
        placePiece(toRow, toCol, p->getIsWhite(), promotionType); // TODO: change placePiece to account for castling
    }

    p->setHasMoved(true);
    notifyObservers();
}

bool ChessBoard::verifyMove(int fromRow, int fromCol, int toRow, int toCol, bool isWhite, char promotionType) {
    if (fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7 || toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7) { return false; }

    Piece* piece = getSquare(fromRow, fromCol);
    if (piece == nullptr) { return false; }
    cout << "check passed: piece exists" << endl;

    // check if a piece can move to the destination; no pieces block path; landing square is empty or occupied by DIFFERENT colour piece
    if (!(piece->checkValidMove(*this, toRow, toCol))) { return false; }
    cout << "check passed: piece can move" << endl;

    // check that after the move, the king is not in check
    if (checkIfKingIsInCheck(isWhite, fromRow, fromCol, toRow, toCol)) { return false; }
    cout << "check passed: king is not in check" << endl;
    
    return true;
}

int ChessBoard::getNumKings(bool isWhite) const {
    int numKings = 0;
    if (isWhite) {
        for (int i = 0; i < whitePieces.size(); ++i) {
            if (whitePieces[i].get()->getPieceType() == 'k') {
                numKings++;
            }
        }
    } else {
        for (int i = 0; i < blackPieces.size(); ++i) {
            if (blackPieces[i].get()->getPieceType() == 'k') {
                numKings++;
            }
        }
    }
    return numKings;
}

Piece* ChessBoard::getEnPassantPawn() const {
    return enPassantPawn;
}
