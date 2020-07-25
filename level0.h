#ifndef _LEVEL0_
#define _LEVEL0_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"

class Level0: public BlockSelectionStrategy{
    public:
        Level0();
        ~Level0();
        Block* getNextBlock();
};

#endif