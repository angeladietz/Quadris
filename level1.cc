#include "level1.h"
#include "blockSelectionStrategy.h"
#include "blockFactory.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default constructor
Level1::Level1(BlockFactory* blockFactory){
    level1_ = new PImpl_bs;
    setBlockProbabilities();
    level1_->areBlocksHeavy_ = false;
    level1_->isRandom_ = true;
    level1_->blockFactory_ = blockFactory;
    setNextBlockType();
}

void Level1::setBlockProbabilities(){
    level1_->blockProbabilities_[SBlock] = 1;
    level1_->blockProbabilities_[ZBlock] = 1;
    level1_->blockProbabilities_[IBlock] = 2;
    level1_->blockProbabilities_[JBlock] = 2;
    level1_->blockProbabilities_[LBlock] = 2;
    level1_->blockProbabilities_[OBlock] = 2;
    level1_->blockProbabilities_[TBlock] = 2;
}

// Destructor
Level1::~Level1(){
    delete level1_;
}

Block* Level1::getNextBlock(){
    Block* b = level1_->blockFactory_->createBlock(level1_->nextBlockType_, level1_->areBlocksHeavy_);
    setNextBlockType();
    return b;
}

BlockType Level1::getNextBlockType(){
    return level1_->nextBlockType_;
}

void Level1::setNextBlockType(){
    int weightSum = 0;

    for (auto const& it : level1_->blockProbabilities_) {
        weightSum += it.second;
    }

    // get a random number >= 0 and < sum of weights
    int rand = std::rand() % weightSum;

    for (auto const& it : level1_->blockProbabilities_) {
        if (rand < it.second){
            level1_->nextBlockType_ = it.first;
            return;
        }
        rand -= it.second;
    }
}

Block* Level1::getBlockOfType(BlockType bType){
    return level1_->blockFactory_->createBlock(bType, level1_->areBlocksHeavy_);
}
