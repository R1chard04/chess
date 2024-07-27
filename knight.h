#ifndef KNIGHT_H
#define KNIGHT_H
#include <vector>
#include <string>
#include "piece.h" 
using namespace std;

class Knight : public Piece {

    public:
        Knight(string pieceColour); 
        virtual ~Knight() = default;

};

#endif
