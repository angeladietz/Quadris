#ifndef _TBLOCK_
#define _TBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class TBlock: public Block {
    public:
        TBlock(Board*, bool);
        ~TBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class TBlockFactory: public BlockFactory{
            Block* create(Board* board, bool isHeavy){
                return new TBlock(board, isHeavy);
            }
        };
};

#endif
