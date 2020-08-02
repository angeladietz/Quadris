#ifndef _ZBLOCK_
#define _ZBLOCK_

#include <iostream>
#include <vector>
#include "board.h"
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class ZBlock: public Block {
    public:
        ZBlock(Board*, bool);
        ~ZBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class ZBlockFactory: public BlockFactory{
            Block* create(Board* board, bool isHeavy){
                return new ZBlock(board, isHeavy);
            }
        };
};

#endif
