#ifndef _LEVEL2_
#define _LEVEL2_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"
#include "blockFactory.h"

class Level2: public BlockSelectionStrategy{
    public:
        Level2(BlockFactory*);
        ~Level2();
        Block* getNextBlock();
        Block* getBlockOfType(BlockType);
        void setRandom(bool){}
        void setSequenceFile(std::string){}
    private:
        void setBlockProbabilities();
        BlockType getNextBlockType();
        PImpl_bs* level2_;
};

#endif