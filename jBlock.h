#ifndef _JBLOCK_
#define _JBLOCK_

#include <iostream>
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockFactory.h"

class JBlock: public Block {
    public:
        JBlock(Board*, bool);
        ~JBlock();

        void rotateClockwise();
        void rotateCounterClockwise();
        class JBlockFactory: public BlockFactory{
            Block* create(Board* board, bool isHeavy){
                return new JBlock(board, isHeavy);
            }
        };
};

#endif
