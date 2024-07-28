#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string> 
using namespace std;

class Piece {
    
    vector<vector<int>> moves; 
    string pieceColour; 
    char pieceType;
    bool hasMoved;

    public:
        Piece(string pieceColour, vector<vector<int>> moves, char pieceType);

        string getColour(); 
        vector<vector<int>> getValidMoves();

        virtual ~Piece() = default;

        bool getIsWhite() const;
        bool getPieceType() const;
        bool getHasMoved() const;


};

#endif
