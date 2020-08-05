#include "tileBlock.h"
#include "block.h"
#include "board.h"

TileBlock::TileBlock(Board *board, bool isHeavy) {

  type = '*';
  blocktype = BlockType::TILE_BLOCK;
  isHeavy_ = isHeavy;
  levelGen_ = board->getLevel();
  createBlock({{5, 3}}, board);
}

TileBlock::~TileBlock() {}
