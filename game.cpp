#include "game.h"


// TODO: remember to replace graphical display init
Game::Game(Xwindow* window): scoreWhite{0}, scoreBlack{0}, textDisplay{make_unique<TextObserver>()},
                            graphicalDisplay{nullptr}, board{make_unique<ChessBoard>(textDisplay.get(), graphicalDisplay.get())},
                            isWhiteTurn{true}, setupMode{false} {}

// Game::Game(Xwindow *w, bool enableGraphics) : in{cin}, out{cout}, turn{Colour::White}, isSetup{false}, enableGraphics{enableGraphics},
// 						 td{make_unique<TextDisplay>()}, gd{enableGraphics ? make_unique<GraphicsDisplay>(8, *w) : nullptr},
// 						 b{make_unique<Board>(td.get(), gd.get())}, scoreWhite{0}, scoreBlack{0} {}

Game::~Game() {}

// SHOULD BE DONE
void Game::setupNormalBoard() {
    board->removeAllPieces();
    isWhiteTurn = true;

    board->placePiece(0, 0, true, 'r');
    board->placePiece(0, 1, true, 'n');
    board->placePiece(0, 2, true, 'b');
    board->placePiece(0, 3, true, 'q');
    board->placePiece(0, 4, true, 'k');
    board->placePiece(0, 5, true, 'b');
    board->placePiece(0, 6, true, 'n');
    board->placePiece(0, 7, true, 'r');

    for (int i = 0; i < 8; i++) {
        board->placePiece(1, i, true, 'p');
        board->placePiece(6, i, false, 'p');
    }

    board->placePiece(7, 0, false, 'r');
    board->placePiece(7, 1, false, 'n');
    board->placePiece(7, 2, false, 'b');
    board->placePiece(7, 3, false, 'q');
    board->placePiece(7, 4, false, 'k');
    board->placePiece(7, 5, false, 'b');
    board->placePiece(7, 6, false, 'n');
    board->placePiece(7, 7, false, 'r');

}

// SHOULD BE DONE
void Game::runTurn() {
    if (isWhiteTurn) {
        pWhite->makeMove(*board);
    } else {
        pBlack->makeMove(*board);
    }
}

void Game::startGame(bool whiteIsHuman, bool blackIsHuman, int whiteDifficulty, int blackDifficulty) {
    isWhiteTurn = true;
    if (whiteIsHuman) {
        pWhite = make_unique<Human>(true);
    } else {
        pWhite = make_unique<Computer>(true, whiteDifficulty);
    }

    if (blackIsHuman) {
        pBlack = make_unique<Human>(false);
    } else {
        pBlack = make_unique<Computer>(false, blackDifficulty);
    }

    if (!setupMode) { setupNormalBoard(); } 

    while (in) {
        // checks for checks, checkmates and stalemates
        if (board->checkIfKingIsInCheck(isWhiteTurn)) {
            string oppositeColourTurn = !isWhiteTurn ? "White" : "Black";
            if (board->checkCheckmate(isWhiteTurn)) {
                out << "Checkmate! " << oppositeColourTurn << " wins!" << endl;
            } else {
                out << oppositeColourTurn << " is in check." << endl;
            }
        }
        if (board->checkStalemate(isWhiteTurn)) {
            out << "Stalemate!" << endl;
        }

        runTurn();
        board->notifyObservers();

        isWhiteTurn = !isWhiteTurn;
    }
}

// ALMOST DONE
void Game::setupBoard() {
    setupMode = true;
    board->removeAllPieces();
    
    string inputLine;
    while (getline(in, inputLine)) {
        istringstream iss{inputLine};
        string command;
        iss >> command;

        if (command == "+") {
            char type;
			char col;
			int row;
			iss >> type >> col >> row;
            
            row--; 
            char lowerCaseType = tolower(type);
            if (row >= 0 && row < 8 && col >= 'a' && col <= 'h' && (lowerCaseType == 'p' || lowerCaseType == 'r' || lowerCaseType == 'n' || lowerCaseType == 'b' || lowerCaseType == 'q' || lowerCaseType == 'k')) {
                // TODO: need something here to indicate that castling is NOT ALLOWED
                cout<<"placing piece: "<<type<<" "<<row<<" "<<int(col - 'a')<<endl;
                board->placePiece(row, int(col - 'a'), type != lowerCaseType, lowerCaseType);
            } else {
                out << "Invalid command in Game::setupBoard (+)" << " "<<type<<" "<<col<<" "<<row<<endl;
            }
        } else if (command == "-") {
            char col;
			int row;
			iss >> col >> row;
            if (row >= 0 && row <= 8 && col >= 'a' && col <= 'h') {
                board->removePiece(row, col);
            } else {
                out << "Invalid command in Game::setupBoard (-)" << endl;
            }
        } else if (command == "=") { // makes it `colour`'s turn to go next
            string colour;
            iss >> colour;

            if (colour == "white") {
                isWhiteTurn = true;
            } else if (colour == "black") {
                isWhiteTurn = false;
            } else {
                out << "Invalid command in Game::setupBoard (=)" << endl;
            }
        } else if (command == "done") { // leave setup mode
            // TODO: verify that the board contains exactly one white king and exactly one black king; that no pawns are on the first or last row of the board; and that neither king is in check.

            setupMode = false;
            break;
        } else {
            out << "Invalid command in Game::setupBoard (\"done\")" << endl;
        }

    }
}

// DONE
void Game::renderScore () const{
    out << "Final Score:" << endl;
	out << "White: " << scoreWhite << endl;
	out << "Black: " << scoreBlack << endl;
}


