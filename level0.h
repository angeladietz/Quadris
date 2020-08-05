#ifndef _LEVEL0_
#define _LEVEL0_

#include "block.h"
#include "blockFactory.h"
#include "blockSelectionStrategy.h"
#include <iostream>
#include <queue>

class Level0 : public BlockSelectionStrategy {
public:
  Level0(BlockFactory *, std::string = "sequence.txt");
  ~Level0();

private:
  void setNextBlockType();
};

#endif