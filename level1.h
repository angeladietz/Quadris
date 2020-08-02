#ifndef _LEVEL1_
#define _LEVEL1_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"
#include "blockFactory.h"

class Level1: public BlockSelectionStrategy{
    public:
        Level1(BlockFactory*);
        ~Level1();
        Block* getNextBlock();
        Block* getBlockOfType(BlockType);
        BlockType getNextBlockType();
        void setRandom(bool){}
        void setSequenceFile(std::string){}
    private:
        void setBlockProbabilities();
        void setNextBlockType();
        PImpl_bs* level1_;
};

#endif
