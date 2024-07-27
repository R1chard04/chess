#ifndef QUEEN_H
#define QUEEN_H
#include <vector>
#include <string>
#include "piece.h" 
using namespace std;

class Queen : public Piece {

    public:
        Queen(string pieceColour); 
        virtual ~Queen() = default;

};

#endif
