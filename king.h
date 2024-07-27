#ifndef KING_H
#define KING_H
#include <vector>
#include <string>
#include "piece.h" 
using namespace std;

class King : public Piece {

    public:
        King(string pieceColour); 
        virtual ~King() = default;

};

#endif
