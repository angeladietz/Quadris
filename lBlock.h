#ifndef _LBLOCK_
#define _LBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class LBlock: public Block {
    public:
        LBlock();
        ~LBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class LBlockFactory: public BlockFactory{};
};

#endif