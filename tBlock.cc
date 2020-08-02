#include "tBlock.h"
#include "board.h"

TBlock::TBlock(Board *board, bool isHeavy) {
   
    type = 'T';
    blocktype = BlockType::TBlock;
    isHeavy_ = isHeavy;
    levelGen_ = board->getLevel();
    createBlock({{0,3}, {1,3}, {2,3}, {1,4}}, board);

}

TBlock::~TBlock() {}
