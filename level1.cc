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
    BlockType type = getNextBlockType();
    return level1_->blockFactory_->createBlock(type, level1_->areBlocksHeavy_);
}

BlockType Level1::getNextBlockType(){
    int weightSum = 0;

    for (auto const& it : level1_->blockProbabilities_) {
        weightSum += it.second;
    }

    // get a random number >= 0 and < sum of weights
    int rand = std::rand() % weightSum;

    for (auto const& it : level1_->blockProbabilities_) {
        if (rand < it.second){
            return it.first;
        }
        rand -= it.second;
    }
}

Block* Level1::getBlockOfType(BlockType bType){
    return level1_->blockFactory_->createBlock(bType, level1_->areBlocksHeavy_);
}
