#include "level3.h"
#include "blockSelectionStrategy.h"
#include "blockFactory.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default constructor
Level3::Level3(BlockFactory* blockFactory, bool isRandom){
    level3_ = new PImpl_bs;
    setBlockProbabilities();
    level3_->areBlocksHeavy_ = true;
    level3_->isRandom_ = isRandom;
    level3_->blockFactory_ = blockFactory;
    setNextBlockType();
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
    return level3_->nextBlockType_;
}

void Level3::setNextBlockType(){
    if (level3_->isRandom_){
        level3_->nextBlockType_ = getNextRandBlockType();
    }
    else{
        level3_->nextBlockType_ = getNextNonRandBlockType();
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
    if (level3_->blockList_.size() == 0){
        return INVALID_BLOCK;
    }

    BlockType bType = level3_->blockList_.at(level3_->blockIndex_);
    updateBlockIndex();
    return bType;
}

void Level3::updateBlockIndex(){
    level3_->blockIndex_++;
    if (level3_->blockIndex_ >= level3_->blockList_.size() - 1){
        level3_->blockIndex_ = 0;
    }
}

void Level3::setRandom(bool isRandom){
    level3_->isRandom_ = isRandom;
}

void Level3::setSequenceFile(string filename){
    level3_->sequenceFile_ = filename;
    level3_->blockList_.clear();
    readSequenceFile();
}

void Level3::readSequenceFile(){
    ifstream blockFile;

    //TODO: ADD EXCEPTION HANDLING!
    blockFile.open(level3_->sequenceFile_);

    if (blockFile.is_open()){
        char nextBlock;
        while(blockFile>>nextBlock){
            BlockType bType = getBlockType(nextBlock);
            if (bType != INVALID_BLOCK){
                level3_->blockList_.push_back(bType);
            }
        }
        blockFile.close();
    }
}

Block* Level3::getBlockOfType(BlockType bType){
    return level3_->blockFactory_->createBlock(bType, level3_->areBlocksHeavy_);
}
