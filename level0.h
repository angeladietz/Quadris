#ifndef _LEVEL0_
#define _LEVEL0_

#include <iostream>
#include <queue>
#include "blockSelectionStrategy.h"
#include "block.h"

struct PImpl_L0{
    std::queue<BlockType> blockList_;
};

class Level0: public BlockSelectionStrategy{
    public:
        Level0(std::string);
        ~Level0();
        Block* getNextBlock();
    private:
        BlockType getNextBlockType();
        PImpl_L0* level0_;
};

#endif