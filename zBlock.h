#ifndef _ZBLOCK_
#define _ZBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class ZBlock: public Block {
    public:
        ZBlock();
        ~ZBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class ZBlockFactory: public BlockFactory{};
};

#endif