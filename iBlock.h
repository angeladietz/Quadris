#ifndef _IBLOCK_
#define _IBLOCK_

#include "block.h"
#include "blockFactory.h"
#include "tile.h"
#include <iostream>
#include <vector>

class IBlock : public Block {
public:
  IBlock(Board *, bool);
  ~IBlock();

  void rotateClockwise();
  void rotateCounterClockwise();

  class IBlockFactory : public BlockFactory {
    Block *create(Board *board, bool isHeavy) {
      return new IBlock(board, isHeavy);
    }
  };
};

#endif
