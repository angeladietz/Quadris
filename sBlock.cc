#include "sBlock.h"
#include "board.h"

SBlock::SBlock(Board *board, bool isHeavy) {
   
    type = 'S';
    blocktype = BlockType::SBlock;
    isHeavy_ = isHeavy;
    levelGen_ = board->getLevel();
    createBlock({{1,3}, {2,3}, {0,4}, {1,4}}, board);

}

SBlock::~SBlock() {}
