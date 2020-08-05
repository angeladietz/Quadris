#include "level2.h"
#include "blockFactory.h"
#include "blockSelectionStrategy.h"
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

// Default constructor
Level2::Level2(BlockFactory *blockFactory) {
  level_ = new PImpl_bs;
  setBlockProbabilities();
  level_->areBlocksHeavy_ = false;
  level_->isRandom_ = true;
  level_->blockFactory_ = blockFactory;
  setNextBlockType();
}

void Level2::setBlockProbabilities() {
  level_->blockProbabilities_[SBlock] = 1;
  level_->blockProbabilities_[ZBlock] = 1;
  level_->blockProbabilities_[IBlock] = 1;
  level_->blockProbabilities_[JBlock] = 1;
  level_->blockProbabilities_[LBlock] = 1;
  level_->blockProbabilities_[OBlock] = 1;
  level_->blockProbabilities_[TBlock] = 1;
}

// Destructor
Level2::~Level2() { delete level_; }

void Level2::setNextBlockType() {
  level_->nextBlockType_ = getNextRandBlockType();
}
