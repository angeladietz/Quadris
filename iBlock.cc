#include "iBlock.h"
#include "block.h"
#include "board.h"

IBlock::IBlock(Board *board, bool isHeavy) {

  type = 'I';
  blocktype = BlockType::IBlock;
  isHeavy_ = isHeavy;
  levelGen_ = board->getLevel();
  createBlock({{0, 3}, {1, 3}, {2, 3}, {3, 3}}, board);
}

IBlock::~IBlock() {}
