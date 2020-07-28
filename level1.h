#ifndef _LEVEL1_
#define _LEVEL1_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"

struct PImpl_l1{
    std::map<BlockType, float> blockProbabilities_;
};

class Level1: public BlockSelectionStrategy{
    public:
        Level1();
        ~Level1();
        Block* getNextBlock();
    private:
        void setBlockProbabilities();
        BlockType getNextBlockType();
        PImpl_l1* level1_;
};

#endif