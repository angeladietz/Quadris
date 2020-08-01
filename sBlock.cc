#include "sBlock.h"

SBlock::SBlock(Board *board) {
   
    type = 'S';
    blocktype = BlockType::SBlock;
    createBlock({{1,3}, {2,3}, {0,4}, {1,4}}, board);

}

SBlock::~SBlock() {}
