#ifndef _LEVEL3_
#define _LEVEL3_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"
#include "blockFactory.h"

class Level3: public BlockSelectionStrategy{
    public:
        Level3(BlockFactory*, bool);
        ~Level3();
        Block* getNextBlock();
        Block* getBlockOfType(BlockType);
        void setRandom(bool);
        void setSequenceFile(std::string);
    private:
        void setBlockProbabilities();
        BlockType getNextBlockType();
        BlockType getNextRandBlockType();
        BlockType getNextNonRandBlockType();
        void updateBlockIndex();
        void readSequenceFile();
        PImpl_bs* level3_;
        bool isRandom_;
};

#endif
