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

    unique_ptr<Xwindow> window = make_unique<Xwindow>(680, 680);
    // unique_ptr<Xwindow> window = nullptr;

    Game game {window.get()};
    // Game game = Game{nullptr};

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
                int difficulty = static_cast<int>(blackPlayer.back()) - '0';
                cout << "diff: " << difficulty << endl;
                game.startGame(true, false, -1, difficulty);
            } else if (!whiteIsHuman && blackIsHuman) {
                int difficulty = static_cast<int>(whitePlayer.back()) - '0';
                game.startGame(false, true, difficulty, -1);
            } else {
                int whiteDifficulty = static_cast<int>(whitePlayer.back()) - '0';
                int blackDifficulty = static_cast<int>(blackPlayer.back()) - '0';
                game.startGame(false, false, whiteDifficulty, blackDifficulty);
            }

        } else if (command == "setup") {
            game.setupBoard();
        } else {
            cout << "Invalid command in main.cc" << endl;
        }
    }

    game.renderScore();
    return 0;
}
