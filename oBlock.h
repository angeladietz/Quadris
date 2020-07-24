#ifndef _OBLOCK_
#define _OBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class OBlock: public Block {
    public:
        OBlock();
        ~OBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class OBlockFactory: public BlockFactory;
};

#endif