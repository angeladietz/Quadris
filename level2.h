#ifndef _LEVEL2_
#define _LEVEL2_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"

class Level2: public BlockSelectionStrategy{
    public:
        Level2();
        ~Level2();
        Block* getNextBlock();
    private:
        void setBlockProbabilities();
        BlockType getNextBlockType();
        PImpl_bs* level2_;
};

#endif