#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include "player.h"
#include "human.h"
#include "computer.h"
#include "chessboard.h"
#include "window.h"
#include "textobserver.h"
#include "graphicalobserver.h"

class Player;

class Game {
    std::unique_ptr<Player> pWhite;
    std::unique_ptr<Player> pBlack;
    float scoreWhite;
    float scoreBlack;

    // Displays
    std::unique_ptr<TextObserver> textDisplay;
    std::unique_ptr<GraphicalObserver> graphicalDisplay;

    std::unique_ptr<ChessBoard> board; 
    bool isWhiteTurn;
    bool setupMode;

    // IO streams
    std::istream &in = std::cin;
    std::ostream &out = std::cout;

    public:
        Game(Xwindow* window);

        void startGame(bool whiteIsHuman, bool blackIsHuman, int whiteDifficulty, int blackDifficulty);
        void setupNormalBoard();
        void setupBoard();  
        void renderScore() const; 
        bool runTurn(); 

        virtual ~Game();

};

#endif
