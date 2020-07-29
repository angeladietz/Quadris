#ifndef _JBLOCK_
#define _JBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class JBlock: public Block {
    public:
        JBlock();
        ~JBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class JBlockFactory: public BlockFactory{
            Block* create(bool){};
        };
};

#endif