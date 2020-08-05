#include "level3.h"
#include "blockFactory.h"
#include "blockSelectionStrategy.h"
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

// Default constructor
Level3::Level3(BlockFactory *blockFactory, bool isRandom) {
  level_ = new PImpl_bs;
  setBlockProbabilities();
  level_->areBlocksHeavy_ = true;
  level_->isRandom_ = isRandom;
  level_->blockFactory_ = blockFactory;
  setNextBlockType();
}

void Level3::setBlockProbabilities() {
  level_->blockProbabilities_[SBlock] = 2;
  level_->blockProbabilities_[ZBlock] = 2;
  level_->blockProbabilities_[IBlock] = 1;
  level_->blockProbabilities_[JBlock] = 1;
  level_->blockProbabilities_[LBlock] = 1;
  level_->blockProbabilities_[OBlock] = 1;
  level_->blockProbabilities_[TBlock] = 1;
}

// Destructor
Level3::~Level3() { delete level_; }

void Level3::setNextBlockType() {
  if (level_->isRandom_) {
    level_->nextBlockType_ = getNextRandBlockType();
  } else {
    level_->nextBlockType_ = getNextNonRandBlockType();
  }
}
