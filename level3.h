#ifndef _LEVEL3_
#define _LEVEL3_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"

class Level3: public BlockSelectionStrategy{
    public:
        Level3();
        ~Level3();
        Block* getNextBlock();
        void setRandom(bool);
        void setSequenceFile(std::string);
    private:
        void setBlockProbabilities();
        BlockType getNextBlockType();
        BlockType getNextRandBlockType();
        BlockType getNextNonRandBlockType();
        PImpl_bs* level3_;
        bool isRandom_;
};

#endif