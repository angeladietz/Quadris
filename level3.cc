#include "level3.h"
#include "blockSelectionStrategy.h"
#include "blockFactory.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default constructor
Level3::Level3(BlockFactory* blockFactory){
    level3_ = new PImpl_bs;
    setBlockProbabilities();
    level3_->areBlocksHeavy_ = true;
    level3_->isRandom_ = true;
    level3_->blockFactory_ = blockFactory;
}

void Level3::setBlockProbabilities(){
    level3_->blockProbabilities_[SBlock] = 2;
    level3_->blockProbabilities_[ZBlock] = 2;
    level3_->blockProbabilities_[IBlock] = 1;
    level3_->blockProbabilities_[JBlock] = 1;
    level3_->blockProbabilities_[LBlock] = 1;
    level3_->blockProbabilities_[OBlock] = 1;
    level3_->blockProbabilities_[TBlock] = 1;
}

// Destructor
Level3::~Level3(){
    delete level3_;
}

Block* Level3::getNextBlock(){
    BlockType type = getNextBlockType();
    return level3_->blockFactory_->createBlock(type, level3_->areBlocksHeavy_);
}

BlockType Level3::getNextBlockType(){
    if (level3_->isRandom_){
        return getNextRandBlockType();
    }
    else{
        return getNextNonRandBlockType();
    }
}

BlockType Level3::getNextRandBlockType(){
    int weightSum = 0;

    for (auto const& it : level3_->blockProbabilities_) {
        weightSum += it.second;
    }

    // get a random number >= 0 and < sum of weights
    int rand = std::rand() % weightSum;

    for (auto const& it : level3_->blockProbabilities_) {
        if (rand < it.second){
            return it.first;
        }
        rand -= it.second;
    }
}

BlockType Level3::getNextNonRandBlockType(){
    //TODO
    return INVALID_BLOCK;
}

void Level3::setRandom(bool isRandom){
    level3_->isRandom_ = isRandom;
}

void Level3::setSequenceFile(string filename){
    level3_->sequenceFile_ = filename;
}

Block* Level3::getBlockOfType(BlockType bType){
    return level3_->blockFactory_->createBlock(bType, level3_->areBlocksHeavy_);
}
