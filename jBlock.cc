#include "jBlock.h"
#include "board.h"

JBlock::JBlock(Board *board, bool isHeavy) {

  type = 'J';
  blocktype = BlockType::JBlock;
  isHeavy_ = isHeavy;
  levelGen_ = board->getLevel();
  createBlock({{0, 3}, {0, 4}, {1, 4}, {2, 4}}, board);
}

JBlock::~JBlock() {}
