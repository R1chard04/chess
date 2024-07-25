#ifndef GAME_H
#define GAME_H
#include <vector>
#include "player.h"
#include "chessBoard.h"
using namespace std;

class Player;
class Game {
    Player *p1; 
    Player *p2;
    ChessBoard* board; 

    bool isWhiteTurn; 

    public:
        Game(); // maybe consider another that takes in a chessboard state
        Game(ChessBoard *board);

        void startGame(); // maybe take in a checssboard state? 
        void setupBoard();  
        vector<int> renderScore(); 
        void runTurn(); 

        virtual ~Game();



};

#endif
