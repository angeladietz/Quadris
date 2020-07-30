#ifndef _LEVEL4_
#define _LEVEL4_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"
#include "blockFactory.h"

class Level4: public BlockSelectionStrategy{
    public:
        Level4(BlockFactory*);
        ~Level4();
        Block* getNextBlock();
        Block* getBlockOfType(BlockType);
        void setRandom(bool);
        void setSequenceFile(std::string);
};

#endif