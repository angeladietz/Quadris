#include "block.h"
#include "iBlock.h"
#include "board.h"

IBlock::IBlock(Board *board) {
   
    type = 'I';
    blocktype = BlockType::IBlock;
    createBlock({{0,3}, {1,3}, {2,3}, {3,3}}, board);

}

IBlock::~IBlock() {}
