#ifndef _LEVEL4_
#define _LEVEL4_

#include <iostream>
#include <vector>
#include "blockSelectionStrategy.h"
#include "block.h"

class Level4: public BlockSelectionStrategy{
    public:
        Level4();
        ~Level4();
        Block* getNextBlock();
};

#endif