#ifndef _TILE_
#define _TILE_

#include <iostream>
#include <ostream>

#include "location.h"

//Forward declaration of Board class
class Board;

//Forward declaration of Block Class
class Block;

class Tile {
    public:
        Tile(int, int, char = ' ');
        ~Tile() {};

        bool isFilled() const;
        char getTileValue() const;
        void setTileValue(const char);
        int  getXCoordinate();
        int  getYCoordinate();
        void deleteFromBlock();
        void moveDownOneRow(Board*);
        Block* getBlock();
        void setBlock(Block*);
        bool isLastTileFromBlock();

        friend std::ostream& operator<< (std::ostream&, Tile&);

    private:
        char tileValue_;
        Location location_;
        Block* block_;
};

#endif
