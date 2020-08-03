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
        void setSequenceFile(std::string){}
    private:
        void setBlockProbabilities();
        void setNextBlockType();
};

#endif
