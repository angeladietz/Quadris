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
        void deleteTileFromRow();
        void moveDownOneRow(Board*);
        bool isLastTileFromBlock();
        Block* getBlock();

        friend std::ostream& operator<< (std::ostream&, Tile&);

    private:
        char tile_;
        Location location_;
        bool isFilled_ = false;
};

char Tile::getTileValue() const {
    return tile_;
}

bool Tile::isFilled() const {
    return isFilled_;
}

Tile::Tile(int x, int y, char tile) : location_(x, y) {
   tile_ = tile; 
}

void Tile::setTileValue(const char tile) {
    tile_ = tile;
}

#endif
