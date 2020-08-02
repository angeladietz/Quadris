#include "level0.h"
#include "blockSelectionStrategy.h"
#include "block.h"
#include <exception>
#include <fstream>

using namespace std;

// Constructor
Level0::Level0(BlockFactory* blockFactory, string filename){
    level0_ = new PImpl_bs;
    level0_->areBlocksHeavy_ = false;
    level0_->blockFactory_ = blockFactory;
    level0_->blockIndex_ = 0;

    ifstream blockFile;

    //TODO: ADD EXCEPTION HANDLING!
    try {
        blockFile.open(filename);
    } catch (const ifstream::failure& e) {
        std::cerr << "Exception occurred file handling file";
    }

    if (blockFile.is_open()){

        char nextBlock;
        while(blockFile>>nextBlock){
            BlockType bType = getBlockType(nextBlock);
            if (bType != INVALID_BLOCK){
                level0_->blockList_.push_back(bType);
            }
        }
        blockFile.close();
    }
    if (level0_->blockList_.size() == 0){
        level0_->blockIndex_ = -1;
    }
}

// Destructor
Level0::~Level0(){
    delete level0_;
}

Block* Level0::getNextBlock(){
    BlockType type = getNextBlockType();
    Block* b = level0_->blockFactory_->createBlock(type, level0_->areBlocksHeavy_);
    return b;
}

BlockType Level0::getNextBlockType(){
    if (level0_->blockIndex_ == -1){
        return OBlock;
    }

    BlockType bType = level0_->blockList_.at(level0_->blockIndex_);
    updateBlockIndex();
    return bType;
}

void Level0::updateBlockIndex(){
    level0_->blockIndex_++;
    if (level0_->blockIndex_++ >= level0_->blockList_.size()){
        level0_->blockIndex_ = 0;
    }
}

Block* Level0::getBlockOfType(BlockType bType){
    return level0_->blockFactory_->createBlock(bType, level0_->areBlocksHeavy_);
}
