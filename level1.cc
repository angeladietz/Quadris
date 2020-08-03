#include "level1.h"
#include "blockSelectionStrategy.h"
#include "blockFactory.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default constructor
Level1::Level1(BlockFactory* blockFactory){
    level_ = new PImpl_bs;
    setBlockProbabilities();
    level_->areBlocksHeavy_ = false;
    level_->isRandom_ = true;
    level_->blockFactory_ = blockFactory;
    setNextBlockType();
}

void Level1::setBlockProbabilities(){
    level_->blockProbabilities_[SBlock] = 1;
    level_->blockProbabilities_[ZBlock] = 1;
    level_->blockProbabilities_[IBlock] = 2;
    level_->blockProbabilities_[JBlock] = 2;
    level_->blockProbabilities_[LBlock] = 2;
    level_->blockProbabilities_[OBlock] = 2;
    level_->blockProbabilities_[TBlock] = 2;
}

// Destructor
Level1::~Level1(){
    delete level_;
}

void Level1::setNextBlockType(){
    level_->nextBlockType_ = getNextRandBlockType();
}
