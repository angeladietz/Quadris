#ifndef _LEVEL3_
#define _LEVEL3_

#include "block.h"
#include "blockFactory.h"
#include "blockSelectionStrategy.h"
#include <iostream>
#include <vector>

class Level3 : public BlockSelectionStrategy {
public:
  Level3(BlockFactory *, bool);
  ~Level3();

private:
  void setBlockProbabilities();
  void setNextBlockType();
};

#endif
