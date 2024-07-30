#include "human.h"
#include "piece.h"

Human::Human(bool isWhite): Player{isWhite} {}

bool Human::makeMove(ChessBoard& board) {
    string inputLine;

    while(getline(in, inputLine)) {
        istringstream iss{inputLine};
        string command;
        iss >> command;

        if (command == "resign") {
            return false;
        } else if (command == "move") {
            char startCol;
            int startRow;
            char endCol;
            int endRow;
            char promotionType;
            iss >> startCol >> startRow >> endCol >> endRow;

            startRow--; 
            endRow--;

            int startColNum = int(startCol - 'a'); 
            int endColNum = int(endCol - 'a'); 

            // cout << "COORDS:" << startRow << " " << endRow << " " << startColNum << " " << endColNum << " "<<startCol<<" "<<endCol<< endl;

            if (startRow >= 0 && startRow < 8 && startCol >= 'a' && startCol <= 'h' && endRow >= 0 && endRow < 8 && endCol >= 'a' && endCol <= 'h') {
                if (iss >> promotionType) { // check if there the move is a promotion
                    char lowercasePromotionType = tolower(promotionType);
                    if (lowercasePromotionType == 'r' || lowercasePromotionType == 'n' || lowercasePromotionType == 'b' || lowercasePromotionType == 'q') {
                        Piece* piece = board.getSquare(startRow, startColNum);
                        if (piece == nullptr) { cerr << "No piece at start position in Human::makeMove" << endl; }
                        else if (piece->getIsWhite() != isWhite) { cerr << "Invalid piece at start position in Human::makeMove" << endl; } 
                        else if (piece->getPieceType() != 'p') { cerr << "Invalid piece type at start position in Human::makeMove" << endl; }
                        else {
                            if (board.verifyMove(startRow, startColNum, endRow, endColNum, promotionType)) {
                                board.movePiece(startRow, startColNum, endRow, endColNum, promotionType);
                                return true;
                            } else {
                                cerr << "Invalid move in Human::makeMove" << endl;
                            }
                        }
                    } else {
                        cerr << "Invalid promotion type in Human::makeMove" << endl;
                    }
                } else { // move is not a promotion
                    Piece* piece = board.getSquare(startRow, startColNum);
                    if (piece == nullptr) { cerr << "No piece at start position in Human::makeMove" << endl; }
                    else if (piece->getIsWhite() ^ isWhite) { cerr << "Invalid piece at start position in Human::makeMove" << endl; }
                    else {
                        // cout << "color: " << piece->getIsWhite() << " type: " << piece->getPieceType();
                        if (board.verifyMove(startRow, startColNum, endRow, endColNum, isWhite)) {
                            // cout << "moving piece" << endl;
                            board.movePiece(startRow, startColNum, endRow, endColNum);
                            return true;
                        } else {
                            cerr << "Invalid move in Human::makeMove" << endl;
                        }
                    }
                }
            } else {
                cerr << "Invalid move in Human::makeMove" << endl;
            }
        } else {
            cerr << "Invalid command in Human::makeMove" << endl;
        }
    }
    
    return true; // this should never be reached -- added just to suppress compiler warning
}
