#include "jBlock.h"
#include "board.h"

JBlock::JBlock(Board *board) {
   
    type = 'J';
    blocktype = BlockType::JBlock;
    createBlock({{0,3}, {0,4}, {1,4}, {2,4}}, board);

}

JBlock::~JBlock() {}
