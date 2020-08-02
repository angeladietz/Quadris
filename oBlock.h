#ifndef _OBLOCK_
#define _OBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class OBlock: public Block {
    public:
        OBlock(Board*, bool);
        ~OBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class OBlockFactory: public BlockFactory{
            Block* create(Board* board, bool isHeavy){
                return new OBlock(board, isHeavy);
            }
        };
};

#endif
