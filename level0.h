#ifndef _LEVEL0_
#define _LEVEL0_

#include <iostream>
#include <queue>
#include "blockSelectionStrategy.h"
#include "block.h"
#include "blockFactory.h"

class Level0: public BlockSelectionStrategy{
    public:
        Level0(BlockFactory*, Board*, std::string="sequence.txt");
        ~Level0();

    private:
        void setNextBlockType();
};

#endif
