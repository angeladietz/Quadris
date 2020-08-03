#ifndef _LEVEL0_
#define _LEVEL0_

#include <iostream>
#include <queue>
#include "blockSelectionStrategy.h"
#include "block.h"
#include "blockFactory.h"

class Level0: public BlockSelectionStrategy{
    public:
        Level0(BlockFactory*, std::string="sequence.txt");
        ~Level0();
        
        void setRandom(bool){};
        void setSequenceFile(std::string){};
    private:
        void setNextBlockType();
};

#endif