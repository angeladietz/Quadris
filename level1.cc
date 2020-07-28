#include "level1.h"
#include "blockSelectionStrategy.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default onstructor
Level1::Level1(){
    level1_ = new PImpl_bs;
    setBlockProbabilities();
    areBlocksHeavy_ = false;
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
    return blockFactory_->createBlock(type, areBlocksHeavy_);
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