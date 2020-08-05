#ifndef _JBLOCK_
#define _JBLOCK_

#include "block.h"
#include "blockFactory.h"
#include "tile.h"
#include <iostream>
#include <vector>

class JBlock : public Block {
public:
  JBlock(Board *, bool);
  ~JBlock();

  void rotateClockwise();
  void rotateCounterClockwise();
  class JBlockFactory : public BlockFactory {
    Block *create(Board *board, bool isHeavy) {
      return new JBlock(board, isHeavy);
    }
  };
};

#endif
