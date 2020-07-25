#ifndef _LEVEL1_
#define _LEVEL1_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"

class Level1: public BlockSelectionStrategy{
    public:
        Level1();
        ~Level1();
        Block* getNextBlock();
};

#endif