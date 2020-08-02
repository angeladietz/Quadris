#ifndef _IBLOCK_
#define _IBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class IBlock: public Block {
    public:
        IBlock(Board*, bool);
        ~IBlock();

        void rotateClockwise();
        void rotateCounterClockwise();

        class IBlockFactory: public BlockFactory{
            Block* create(Board* board, bool isHeavy){
                return new IBlock(board, isHeavy);
            }
        };
};

#endif
