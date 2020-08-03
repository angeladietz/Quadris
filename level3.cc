#include "level3.h"
#include "blockSelectionStrategy.h"
#include "blockFactory.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default constructor
Level3::Level3(BlockFactory* blockFactory, bool isRandom){
    level_ = new PImpl_bs;
    setBlockProbabilities();
    level_->areBlocksHeavy_ = true;
    level_->isRandom_ = isRandom;
    level_->blockFactory_ = blockFactory;
    setNextBlockType();
}

void Level3::setBlockProbabilities(){
    level_->blockProbabilities_[SBlock] = 2;
    level_->blockProbabilities_[ZBlock] = 2;
    level_->blockProbabilities_[IBlock] = 1;
    level_->blockProbabilities_[JBlock] = 1;
    level_->blockProbabilities_[LBlock] = 1;
    level_->blockProbabilities_[OBlock] = 1;
    level_->blockProbabilities_[TBlock] = 1;
}

// Destructor
Level3::~Level3(){
    delete level_;
}

void Level3::setNextBlockType(){
    if (level_->isRandom_){
        level_->nextBlockType_ = getNextRandBlockType();
    }
    else{
        level_->nextBlockType_ = getNextNonRandBlockType();
    }
}

BlockType Level3::getNextRandBlockType(){
    int weightSum = 0;

    for (auto const& it : level_->blockProbabilities_) {
        weightSum += it.second;
    }

    // get a random number >= 0 and < sum of weights
    int rand = std::rand() % weightSum;

    for (auto const& it : level_->blockProbabilities_) {
        if (rand < it.second){
            return it.first;
        }
        rand -= it.second;
    }
}

BlockType Level3::getNextNonRandBlockType(){
    if (level_->blockList_.size() == 0){
        return INVALID_BLOCK;
    }

    BlockType bType = level_->blockList_.at(level_->blockIndex_);
    updateBlockIndex();
    return bType;
}

void Level3::setSequenceFile(string filename){
    level_->sequenceFile_ = filename;
    level_->blockList_.clear();
    readSequenceFile();
}

void Level3::readSequenceFile(){
    ifstream blockFile;

    //TODO: ADD EXCEPTION HANDLING!
    blockFile.open(level_->sequenceFile_);

    if (blockFile.is_open()){
        char nextBlock;
        while(blockFile>>nextBlock){
            BlockType bType = getBlockType(nextBlock);
            if (bType != INVALID_BLOCK){
                level_->blockList_.push_back(bType);
            }
        }
        blockFile.close();
    }
}
