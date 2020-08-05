#include "zBlock.h"

ZBlock::ZBlock(Board *board, bool isHeavy) {

  type = 'Z';
  blocktype = BlockType::ZBlock;
  isHeavy_ = isHeavy;
  levelGen_ = board->getLevel();
  createBlock({{0, 3}, {1, 3}, {1, 4}, {2, 4}}, board);
}

ZBlock::~ZBlock() {}
