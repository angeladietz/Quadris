#ifndef _BLOCK_
#define _BLOCK_

#include <iostream>
#include <vector>
#include "tile.h"

class Block {
    public:
        Block();
        ~Block();

        bool getTilePositions() const;
        virtual void rotateClockwise()=0;
        virtual void rotateCounterClockwise()=0;
        bool isHeavy();

    private:
        std::vector<Tile> tiles;
};

#endif