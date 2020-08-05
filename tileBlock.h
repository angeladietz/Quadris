#ifndef _TILEBLOCK_
#define _TILEBLOCK_

#include "block.h"
#include "blockFactory.h"
#include "tile.h"
#include <iostream>
#include <vector>

class TileBlock : public Block {
public:
  TileBlock(Board *, bool);
  ~TileBlock();

  void rotateClockwise();
  void rotateCounterClockwise();

  class TileBlockFactory : public BlockFactory {
    Block *create(Board *board, bool isHeavy) {
      return new TileBlock(board, isHeavy);
    }
  };
};

#endif
