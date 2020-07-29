#ifndef _IBLOCK_
#define _IBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class IBlock: public Block {
    public:
        IBlock();
        ~IBlock();

        void rotateClockwise();
        void rotateCounterClockwise();

        class IBlockFactory: public BlockFactory{
            Block* create(bool){};
        };
};

#endif