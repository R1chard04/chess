#ifndef BISHOP_H
#define BISHOP_H
#include <vector>
#include <string> 
using namespace std;

class Bishop : public Piece {

    public:
        Bishop(string pieceColour); 
        virtual ~Bishop() = default;

};

#endif
