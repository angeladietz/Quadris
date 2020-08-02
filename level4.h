#ifndef _LEVEL4_
#define _LEVEL4_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"
#include "blockFactory.h"

class Level4: public BlockSelectionStrategy{
    public:
        Level4(BlockFactory*, bool);
        ~Level4();
        Block* getNextBlock();
        Block* getBlockOfType(BlockType);
        BlockType getNextBlockType();

        void setRandom(bool);
        void setSequenceFile(std::string);
    private:
        void setBlockProbabilities();
        void setNextBlockType();
        BlockType getNextRandBlockType();
        BlockType getNextNonRandBlockType();
        void updateBlockIndex();
        void readSequenceFile();
        PImpl_bs* level4_;
};

#endif
