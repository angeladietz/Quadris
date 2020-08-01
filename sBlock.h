#ifndef _SBLOCK_
#define _SBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class SBlock: public Block {
    public:
        SBlock(Board*);
        ~SBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        
        class SBlockFactory: public BlockFactory{
            Block* create(bool){};
        };
};

#endif
