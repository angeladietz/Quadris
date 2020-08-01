#ifndef _ZBLOCK_
#define _ZBLOCK_

#include <iostream>
#include <vector>
#include "board.h"
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class ZBlock: public Block {
    public:
        ZBlock(Board*);
        ~ZBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class ZBlockFactory: public BlockFactory{
            Block* create(bool){};
        };
};

#endif
