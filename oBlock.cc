#include "oBlock.h"
#include "block.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'O';
    blocktype = BlockType::OBlock;
    createBlock({{0,3}, {1,3}, {0,4}, {1,4}}, board);

}

OBlock::~OBlock() {}
