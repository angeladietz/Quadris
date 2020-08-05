#ifndef _LBLOCK_
#define _LBLOCK_

#include "block.h"
#include "blockFactory.h"
#include "tile.h"
#include <iostream>
#include <vector>

class LBlock : public Block {
public:
  LBlock(Board *, bool);
  ~LBlock();

  void rotateClockwise();
  void rotateCounterClockwise();
  class LBlockFactory : public BlockFactory {
    Block *create(Board *board, bool isHeavy) {
      return new LBlock(board, isHeavy);
    }
  };
};

#endif
