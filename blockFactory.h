#ifndef _BLOCKFACTORY_
#define _BLOCKFACTORY_

#include "block.h"

class BlockFactory{
    public:
        BlockFactory();
        ~BlockFactory();
        Block* createBlock(BlockType, bool);
};

#endif