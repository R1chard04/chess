#include "computer.h"
#include "piece.h"

Computer::Computer(bool isWhite, int difficulty): Player{isWhite}, difficulty{difficulty} {}

vector<vector<int> > Computer::generateMoves(ChessBoard& cBoard) {
    int board_size = 8; 
    string playerColour = isWhite ? "white" : "black";
    vector<vector<int> > res; 

    for(int i = 0; i < board_size; i++) {
        for(int j = 0; j < board_size; j++) {
            if(cBoard.getSquare(i, j)->getColour() != playerColour) continue; 

            // square is computer's piece 
            for(int k = 0; k < board_size; k++) {
                for(int h = 0; h < board_size; h++) {
                    if(cBoard.verifyMove(i, j, k, h)) {
                        // valid move
                        res.push_back({i, j, k, h});
                    }
                }
            }
        }
    }
}

bool Computer::makeMove(ChessBoard& cBoard) {

    int board_size = 8;
    string playerColour = isWhite ? "white" : "black";

    if(difficulty == 1) {
        // random legal moves
        // idea: find a piece that is on the board and randomly choose a move 
        vector<vector<int> > moves = generateMoves(cBoard);

        if(moves.size() == 0) return false; // cannot generate a viable move; 

        vector<int> move = moves[0]; 

        // PROMOTION: 
        if(cBoard.getSquare(move[0], move[1])->getPieceType() == 'p' && (move[2] == board_size - 1 || move[2] == 0) ) {
            cBoard.movePiece(move[0], move[1], move[2], move[3], 'q');
        } else {
            cBoard.movePiece(move[0], move[1], move[2], move[3], 'x');
        }
        return true; 
    } else if(difficulty == 2 {
        vector<vector<int> > moves = generateMoves(cBoard); 

        if(moves.size() == 0) return false;

        // move takes a piece: 
        for(int i = 0; i < moves.size(); i++) {
            vector<int> move = moves[i];

            if(cBoard.getSquare(move[2], move[3])->getColour() != playerColour) {
                // takes opponent's piece
                if(cBoard.getSquare(move[0], move[1])->getPieceType() == 'p' && (move[2] == board_size - 1 || move[2] == 0) ) {
                    cBoard.movePiece(move[0], move[1], move[2], move[3], 'q');
                    return true;
                }
                // castling with promotion: 
                cBoard.movePiece(moves[i][0], moves[i][1], moves[i][2], moves[i][3], 'x');
                return true;
            }
        }

        // prefers capturing moves and checks

    } else if(difficulty == 3) {
        // prefers avoiding capture, capturing moves, and checks
    } else if(difficulty == 4) {
        //

    } 

    return true;
}