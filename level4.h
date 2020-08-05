#ifndef _LEVEL4_
#define _LEVEL4_

#include "block.h"
#include "blockFactory.h"
#include "blockSelectionStrategy.h"
#include <iostream>
#include <vector>

class Level4 : public BlockSelectionStrategy {
public:
  Level4(BlockFactory *, bool);
  ~Level4();

  void setSequenceFile(std::string);

private:
  void setBlockProbabilities();
  void setNextBlockType();
};

#endif
