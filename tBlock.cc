#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'T';
    blocktype = BlockType::TBlock;
    createBlock({{0,3}, {1,3}, {2,3}, {1,4}}, board);

}

OBlock::~OBlock() {}
