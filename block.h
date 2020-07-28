#ifndef _BLOCK_
#define _BLOCK_

#include <iostream>
#include <vector>
#include "tile.h"

enum BlockType {IBlock,JBlock,LBlock,SBlock,ZBlock,OBlock,TBlock,INVALID_BLOCK};

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