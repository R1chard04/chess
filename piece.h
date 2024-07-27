#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string> 
using namespace std;

class Piece {
    
    vector<vector<int>> moves; 
    bool isWhite; 
    char pieceType;

    public:
        Piece(bool isWhite);

        string getColour(); 
        vector<vector<int>> getValidMoves();

        virtual ~Piece() = default;

        bool getIsWhite() const;
        bool getPieceType() const;

};

#endif
