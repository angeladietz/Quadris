#include "blockSelectionStrategy.h"
#include "block.h"

using namespace std;

// // Constructor
// BlockSelectionStrategy::BlockSelectionStrategy(BlockFactory* bf){
//     //blockFactory_ = bf;
// }

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

void BlockSelectionStrategy::setSequenceFile(string){}
