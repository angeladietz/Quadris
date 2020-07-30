#include "level2.h"
#include "blockSelectionStrategy.h"
#include "blockFactory.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default constructor
Level2::Level2(BlockFactory* blockFactory){
    level2_ = new PImpl_bs;
    setBlockProbabilities();
    level2_->areBlocksHeavy_ = false;
    level2_->isRandom_ = true;
    level2_->blockFactory_ = blockFactory;
}

void Level2::setBlockProbabilities(){
    level2_->blockProbabilities_[SBlock] = 1;
    level2_->blockProbabilities_[ZBlock] = 1;
    level2_->blockProbabilities_[IBlock] = 1;
    level2_->blockProbabilities_[JBlock] = 1;
    level2_->blockProbabilities_[LBlock] = 1;
    level2_->blockProbabilities_[OBlock] = 1;
    level2_->blockProbabilities_[TBlock] = 1;
}

// Destructor
Level2::~Level2(){
    delete level2_;
}

Block* Level2::getNextBlock(){
    BlockType type = getNextBlockType();
    return level2_->blockFactory_->createBlock(type, level2_->areBlocksHeavy_);
}

BlockType Level2::getNextBlockType(){
    int weightSum = 0;

    for (auto const& it : level2_->blockProbabilities_) {
        weightSum += it.second;
    }

    // get a random number >= 0 and < sum of weights
    int rand = std::rand() % weightSum;

    for (auto const& it : level2_->blockProbabilities_) {
        if (rand < it.second){
            return it.first;
        }
        rand -= it.second;
    }
}

Block* Level2::getBlockOfType(BlockType bType){
    return level2_->blockFactory_->createBlock(bType, level2_->areBlocksHeavy_);
}
