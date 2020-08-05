#include "blockSelectionStrategy.h"
#include "block.h"
#include <fstream>

using namespace std;

// Destructor
BlockSelectionStrategy::~BlockSelectionStrategy(){}


Block* BlockSelectionStrategy::getNextBlock(){
    Block* b = level_->blockFactory_->createBlock(level_->nextBlockType_, level_->areBlocksHeavy_);
    setNextBlockType();
    return b;
}

BlockType BlockSelectionStrategy::getNextBlockType(){
    return level_->nextBlockType_;
}

Block* BlockSelectionStrategy::getBlockOfType(BlockType bType){
    return level_->blockFactory_->createBlock(bType, level_->areBlocksHeavy_);
}

void BlockSelectionStrategy::setRandom(bool isRandom){
    level_->isRandom_ = isRandom;
}

BlockType BlockSelectionStrategy::getNextRandBlockType(){
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

BlockType BlockSelectionStrategy::getNextNonRandBlockType(){
    if (level_->blockList_.size() == 0){
        return INVALID_BLOCK;
    }

    BlockType bType = level_->blockList_.at(level_->blockIndex_);
    updateBlockIndex();
    return bType;
}

void BlockSelectionStrategy::updateBlockIndex(){
    level_->blockIndex_++;
    if (level_->blockIndex_ >= level_->blockList_.size() - 1){
        level_->blockIndex_ = 0;
    }
}

BlockType BlockSelectionStrategy::getBlockType(char c){
    if (tolower(c) == 'i'){
        return IBlock;
    }
    if (tolower(c) == 'j'){
        return JBlock;
    }
    if (tolower(c) == 'l'){
        return LBlock;
    }
    if (tolower(c) == 's'){
        return SBlock;
    }
    if (tolower(c) == 'z'){
        return ZBlock;
    }
    if (tolower(c) == 'o'){
        return OBlock;
    }
    if (tolower(c) == 't'){
        return TBlock;
    }
    return INVALID_BLOCK;
}

void BlockSelectionStrategy::setSequenceFile(string filename){
    level_->sequenceFile_ = filename;
    level_->blockList_.clear();
    readSequenceFile();
}

void BlockSelectionStrategy::readSequenceFile(){
    ifstream blockFile;

    try {
        blockFile.open(level_->sequenceFile_);
    } catch (const ifstream::failure& e){
        std::cerr << "Exception occurred handling file" << level_->sequenceFile_;
    }

    if (blockFile.is_open()){
        char nextBlock;
        while(blockFile>>nextBlock){
            cerr<<nextBlock<<endl;
            BlockType bType = getBlockType(nextBlock);
            if (bType != INVALID_BLOCK){
                level_->blockList_.push_back(bType);
            }
        }
        blockFile.close();
    }
}
