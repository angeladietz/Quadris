#include "oBlock.h"
#include "block.h"
#include "board.h"

OBlock::OBlock(Board *board, bool isHeavy) {
   
    type = 'O';
    blocktype = BlockType::OBlock;
    isHeavy_ = isHeavy;
    levelGen_ = board->getLevel();
    createBlock({{0,3}, {1,3}, {0,4}, {1,4}}, board);

}

OBlock::~OBlock() {}
