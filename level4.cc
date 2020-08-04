#include "level4.h"
#include "blockSelectionStrategy.h"
#include "blockFactory.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default constructor
Level4::Level4(BlockFactory* blockFactory, bool isRandom){
    level_ = new PImpl_bs;
    setBlockProbabilities();
    level_->areBlocksHeavy_ = true;
    level_->isRandom_ = isRandom;
    level_->blockFactory_ = blockFactory;
    level_->blockIndex_ = 0;
    setNextBlockType();
}

void Level4::setBlockProbabilities(){
    level_->blockProbabilities_[SBlock] = 2;
    level_->blockProbabilities_[ZBlock] = 2;
    level_->blockProbabilities_[IBlock] = 1;
    level_->blockProbabilities_[JBlock] = 1;
    level_->blockProbabilities_[LBlock] = 1;
    level_->blockProbabilities_[OBlock] = 1;
    level_->blockProbabilities_[TBlock] = 1;
}

// Destructor
Level4::~Level4(){
    delete level_;
}

void Level4::setNextBlockType(){
    if (level_->isRandom_){
        level_->nextBlockType_ = getNextRandBlockType();
    }
    else{
        level_->nextBlockType_ = getNextNonRandBlockType();
    }
}
