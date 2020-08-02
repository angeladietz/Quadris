#include "level4.h"
#include "blockSelectionStrategy.h"
#include "blockFactory.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default constructor
Level4::Level4(BlockFactory* blockFactory, bool isRandom){
    level4_ = new PImpl_bs;
    setBlockProbabilities();
    level4_->areBlocksHeavy_ = true;
    level4_->isRandom_ = isRandom;
    level4_->blockFactory_ = blockFactory;
    level4_->blockIndex_ = 0;
    setNextBlockType();
}

void Level4::setBlockProbabilities(){
    level4_->blockProbabilities_[SBlock] = 2;
    level4_->blockProbabilities_[ZBlock] = 2;
    level4_->blockProbabilities_[IBlock] = 1;
    level4_->blockProbabilities_[JBlock] = 1;
    level4_->blockProbabilities_[LBlock] = 1;
    level4_->blockProbabilities_[OBlock] = 1;
    level4_->blockProbabilities_[TBlock] = 1;
}

// Destructor
Level4::~Level4(){
    delete level4_;
}

Block* Level4::getNextBlock(){
    BlockType type = getNextBlockType();
    return level4_->blockFactory_->createBlock(type, level4_->areBlocksHeavy_);
}

BlockType Level4::getNextBlockType(){
    return level4_->nextBlockType_;
}

void Level4::setNextBlockType(){
    if (level4_->isRandom_){
        level4_->nextBlockType_ = getNextRandBlockType();
    }
    else{
        level4_->nextBlockType_ = getNextNonRandBlockType();
    }
}

BlockType Level4::getNextRandBlockType(){
    int weightSum = 0;

    for (auto const& it : level4_->blockProbabilities_) {
        weightSum += it.second;
    }

    // get a random number >= 0 and < sum of weights
    int rand = std::rand() % weightSum;

    for (auto const& it : level4_->blockProbabilities_) {
        if (rand < it.second){
            return it.first;
        }
        rand -= it.second;
    }
}

BlockType Level4::getNextNonRandBlockType(){
    if (level4_->blockList_.size() == 0){
        return INVALID_BLOCK;
    }

    BlockType bType = level4_->blockList_.at(level4_->blockIndex_);
    updateBlockIndex();
    return bType;
}


void Level4::updateBlockIndex(){
    level4_->blockIndex_++;
    if (level4_->blockIndex_ >= level4_->blockList_.size() - 1){
        level4_->blockIndex_ = 0;
    }
}

void Level4::setRandom(bool isRandom){
    level4_->isRandom_ = isRandom;
}

void Level4::setSequenceFile(string filename){
    level4_->sequenceFile_ = filename;
    level4_->blockList_.clear();
    readSequenceFile();
}

void Level4::readSequenceFile(){
    ifstream blockFile;

    //TODO: ADD EXCEPTION HANDLING!
    blockFile.open(level4_->sequenceFile_);

    if (blockFile.is_open()){

        char nextBlock;
        while(blockFile>>nextBlock){
            BlockType bType = getBlockType(nextBlock);
            if (bType != INVALID_BLOCK){
                level4_->blockList_.push_back(bType);
            }
        }
        blockFile.close();
    }
}

Block* Level4::getBlockOfType(BlockType bType){
    return level4_->blockFactory_->createBlock(bType, level4_->areBlocksHeavy_);
}
