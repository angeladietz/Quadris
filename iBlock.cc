#include "block.h"
#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'I';
    blocktype = BlockType::IBlock;
    createBlock({{0,3}, {1,3}, {2,3}, {3,3}}, board);

}

OBlock::~OBlock() {}
