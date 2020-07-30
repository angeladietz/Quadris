#ifndef _LEVEL0_
#define _LEVEL0_

#include <iostream>
#include <queue>
#include "blockSelectionStrategy.h"
#include "block.h"
#include "blockFactory.h"

struct PImpl_L0{
    std::queue<BlockType> blockList_;
    bool areBlocksHeavy_;
    BlockFactory* blockFactory_;
};

class Level0: public BlockSelectionStrategy{
    public:
        Level0(BlockFactory*, std::string="sequence.txt");
        ~Level0();
        Block* getNextBlock();
        Block* getBlockOfType(BlockType);
        virtual void setRandom(){};
    private:
        BlockType getNextBlockType();
        PImpl_bs* level0_;
};

#endif