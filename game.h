#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include "player.h"
#include "chessboard.h"
#include "Window.h"
#include "textobserver.h"
#include "graphicalobserver.h"
using namespace std;

class Player;
class Game {
    std::unique_ptr<Player> pWhite;
    std::unique_ptr<Player> pBlack;
    float scoreWhite;
    float scoreBlack;
    std::unique_ptr<ChessBoard> board; 
    bool isWhiteTurn; // TODO: eventually, we need to change this -- what if there are 4 players?
    bool setupMode;

    // Displays
    std::unique_ptr<TextObserver> textDisplay;
    std::unique_ptr<GraphicalObserver> graphicalDisplay;

    // IO streams
    std::istream &in = std::cin;
    std::ostream &out = std::cout;

    public:
        Game(Xwindow* window);
        Game(ChessBoard *board);

        void startGame(bool whiteIsHuman, bool blackIsHuman, int whiteDifficulty, int blackDifficulty);
        void setupBoard();  
        void renderScore() const; 
        void runTurn(); 

        virtual ~Game();



};

#endif
