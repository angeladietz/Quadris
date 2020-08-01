#include "zBlock.h"

ZBlock::ZBlock(Board *board) {
   
    type = 'Z';
    blocktype = BlockType::ZBlock;
    createBlock({{0,3}, {1,3}, {1,4}, {2,4}}, board);

}

ZBlock::~ZBlock() {}
