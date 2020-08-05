#ifndef _LEVEL1_
#define _LEVEL1_

#include "block.h"
#include "blockFactory.h"
#include "blockSelectionStrategy.h"
#include <iostream>
#include <vector>

class Level1 : public BlockSelectionStrategy {
public:
  Level1(BlockFactory *);
  ~Level1();
  void setRandom(bool) {}
  void setSequenceFile(std::string) {}

private:
  void setBlockProbabilities();
  void setNextBlockType();
};

#endif
