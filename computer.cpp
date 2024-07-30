#include "computer.h"
#include "piece.h"

Computer::Computer(bool isWhite, int difficulty): Player{isWhite}, difficulty{difficulty} {}

vector<vector<int>> Computer::generateMoves(ChessBoard& cBoard) {
    int board_size = 8; 
    string playerColour = isWhite ? "white" : "black";
    vector<vector<int>> res; 

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (cBoard.getSquare(i, j) == nullptr) continue; 
            if (cBoard.getSquare(i, j)->getIsWhite() != isWhite) continue; 

            // square is computer's piece 
            for (int k = 0; k < board_size; k++) {
                for (int h = 0; h < board_size; h++) {
                    if (cBoard.verifyMove(i, j, k, h, isWhite)) {
                        res.push_back({i, j, k, h});
                    }
                }
            }
        }
    }
    return res; 
}

bool Computer::makeMove1(ChessBoard& cBoard) {
    int board_size = 8; 
    vector<vector<int>> moves = generateMoves(cBoard);

    if (moves.size() == 0) return false; // cannot generate a viable move; 

    vector<int> move = moves[0]; 

    // pawn promotion 
    if (cBoard.getSquare(move[0], move[1])->getPieceType() == 'p' && (move[2] == board_size - 1 || move[2] == 0) ) {
        cBoard.movePiece(move[0], move[1], move[2], move[3], 'q');
    } else {
        cBoard.movePiece(move[0], move[1], move[2], move[3], 'x');
    }
    return true; 
}

bool Computer::makeMove2(ChessBoard& cBoard) {
    int board_size = 8; 
    string playerColour = isWhite ? "white" : "black";
    string opponentColour = isWhite ? "black" : "white";

    vector<vector<int> > moves = generateMoves(cBoard); 

    if (moves.size() == 0) return false;

    // move takes a piece: 
    for (int i = 0; i < moves.size(); i++) {
        vector<int> move = moves[i];
        if (cBoard.getSquare(move[2], move[3]) == nullptr) continue; 
        if (cBoard.getSquare(move[2], move[3])->getIsWhite() != isWhite) {
            // takes opponent's piece
            if (cBoard.getSquare(move[0], move[1])->getPieceType() == 'p' && (move[2] == board_size - 1 || move[2] == 0) ) {
                // capture with promotion on pawn
                cBoard.movePiece(move[0], move[1], move[2], move[3], 'q');
                return true;
            } else {
                cBoard.movePiece(move[0], move[1], move[2], move[3], 'x');
                return true;
            }
        }
    }

    // move results in check and does not take a piece
    for(int i = 0; i < moves.size(); i++) {
        vector<int> move = moves[i];


        ChessBoard boardAfterMove = ChessBoard(cBoard); 

        // promotion on pawn
        if (cBoard.getSquare(move[0], move[1])->getPieceType() == 'p' && (move[2] == board_size - 1 || move[2] == 0)) {
            boardAfterMove.movePiece(move[0], move[1], move[2], move[3], 'q');
            // make the move and check if there is a check on opponent
            if(boardAfterMove.checkIfKingIsInCheck(!isWhite)) {
                cBoard.movePiece(move[0], move[1], move[2], move[3], 'q');
                return true; 
            } 
        } else {
            boardAfterMove.movePiece(move[0], move[1], move[2], move[3], 'x');
            if (boardAfterMove.checkIfKingIsInCheck(!isWhite)) {
                cBoard.movePiece(move[0], move[1], move[2], move[3], 'x');
                // the move resulted in a check
                return true; 
            } 
        }
    }

    // no checks and takes could be made
    return makeMove1(cBoard);
}


bool Computer::makeMove3(ChessBoard& cBoard) {
    int board_size = 8;
    vector<vector<int> > moves = generateMoves(cBoard);

    cout<<"makeMove 3 made"<<endl; 
    cout<<moves.size()<<endl;
    if (moves.size() == 0) return false;

    // avoid capture 
    for (int i = 0; i < moves.size(); i++) {
        vector<int> move = moves[i];
        // check if the piece is being attacked
        Piece* currentPiece = cBoard.getSquare(move[0], move[1]);
        bool out = cBoard.checkIfPieceIsAttacked(currentPiece, isWhite);

        cout<<"this is run"<<" "<<"piece is: "<< currentPiece->getPieceType()<<" attacked is:"<<out<<endl;
        

        if(!cBoard.checkIfPieceIsAttacked(currentPiece, isWhite)) continue; 
        // don't care if piece not attacked
        cout<<"this is also run"<<endl;

        ChessBoard boardAfterMove = ChessBoard(cBoard); 

        if (cBoard.getSquare(move[0], move[1])->getPieceType() == 'p' && (move[2] == board_size - 1 || move[2] == 0) ) {
            cout<<"monkeyNoBishop"<<endl;
            boardAfterMove.movePiece(move[0], move[1], move[2], move[3], 'q');
            if(!boardAfterMove.checkIfPieceIsAttacked(boardAfterMove.getSquare(move[2], move[3]), isWhite)) {
                cBoard.movePiece(move[0], move[1], move[2], move[3], 'q');
                return true; 
            } 
        } else {
            cout<<"monkeybishop: "<<move[0]<<" "<<move[1]<<" "<<move[2]<<" "<<move[3]<<endl; 
            boardAfterMove.movePiece(move[0], move[1], move[2], move[3]);
            cout<<boardAfterMove.checkIfPieceIsAttacked(boardAfterMove.getSquare(move[2], move[3]), isWhite)<<endl;
            if(!boardAfterMove.checkIfPieceIsAttacked(boardAfterMove.getSquare(move[2], move[3]), isWhite)) {
                cBoard.movePiece(move[0], move[1], move[2], move[3], 'x');
                return true;
            } 
        }
    }
    return makeMove2(cBoard); 
    return false; 
}

bool Computer::makeMove4(ChessBoard& cBoard) {
    
    return makeMove3(cBoard);
}

bool Computer::makeMove(ChessBoard& cBoard) {

    int board_size = 8;
    string playerColour = isWhite ? "white" : "black";
    string opponentColour = isWhite ? "black" : "white";

    string inputLine; 

    while(getline(in, inputLine)) {
        istringstream iss{inputLine}; 
        string command; 
        iss >> command; 
        if (command == "move") {
            if(difficulty == 1) {
                // random legal moves
                // idea: find a piece that is on the board and randomly choose a move 
                return makeMove1(cBoard);
            } else if(difficulty == 2) {
                // prefers capturing moves and checks
                return makeMove2(cBoard);
            } else if(difficulty == 3) {
                // prefers avoiding capture, capturing moves, and checks
                return makeMove3(cBoard);         

            } else if(difficulty == 4) {
                // weighted pieces 
                return makeMove4(cBoard);
            } 
        } else {
            cerr << "Invalid computer command" <<endl;
        }
    }
    return true;
}
