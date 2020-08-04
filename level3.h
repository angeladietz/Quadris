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

    private:
        void setBlockProbabilities();
        void setNextBlockType();
};

#endif
