#ifndef _LBLOCK_
#define _LBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class LBlock: public Block {
    public:
        LBlock(Board*, bool);
        ~LBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class LBlockFactory: public BlockFactory{
            Block* create(Board* board, bool isHeavy){
                return new LBlock(board, isHeavy);
            }
        };
};

#endif
