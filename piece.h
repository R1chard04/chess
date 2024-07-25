#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string> 
using namespace std;

class Piece {
    
    vector<vector<int>> moves; 
    string colour; 
    public:
        Piece(string col);
        Piece(); 

        string getColour(); 
        vector<vector<int>> getValidMoves();

        virtual ~Piece() = default;



};

#endif
