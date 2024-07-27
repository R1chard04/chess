#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include <memory>
#include "window.h"
#include "game.h"

using namespace std;

// TODO: check for invalid inputs... MOSTLY DONE
int main(int argc, char *argv[]) {
    // Add a flag check if we are in "bonus" mode
    
    unique_ptr<Xwindow> window = make_unique<Xwindow>(400, 400);

    Game game = Game{window.get()};

    string inputLine;
    while (getline(cin, inputLine)) {
        istringstream iss{inputLine};
        string command, whitePlayer, blackPlayer; 
        iss >> command >> whitePlayer >> blackPlayer;

        if (command == "game") {
            bool whiteIsHuman = whitePlayer == "human";
            bool blackIsHuman = blackPlayer == "human";

            if (whiteIsHuman && blackIsHuman) {
                game.startGame(true, true, -1, -1);
            } else if (whiteIsHuman && !blackIsHuman) {
                int difficulty = stoi(blackPlayer.back());
                game.startGame(true, false, -1, difficulty);
            } else if (!whiteIsHuman && blackIsHuman) {
                int difficulty = stoi(whitePlayer.back());
                game.startGame(false, true, difficulty, -1);
            } else {
                int whiteDifficulty = stoi(whitePlayer.back());
                int blackDifficulty = stoi(blackPlayer.back());
                game.startGame(false, false, whiteDifficulty, blackDifficulty);
            }

        } else if (command == "setup") {
            game.setupBoard();
        } else {
            cout << "Invalid command in main.cc" << endl;
        }
    }

    game.renderScore(); // show be called after ctrl+d is pressed, so maybe put this in some destructor?
    return 0;
}

