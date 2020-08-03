#include "level0.h"
#include "blockSelectionStrategy.h"
#include "block.h"
#include <exception>
#include <fstream>

using namespace std;

// Constructor
Level0::Level0(BlockFactory* blockFactory, string filename){
    level_ = new PImpl_bs;
    level_->areBlocksHeavy_ = false;
    level_->blockFactory_ = blockFactory;
    level_->blockIndex_ = 0;

    ifstream blockFile;

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
                level_->blockList_.push_back(bType);
            }
        }
        blockFile.close();
    }
    if (level_->blockList_.size() == 0){
        level_->blockIndex_ = -1;
    }
    setNextBlockType();
}

// Destructor
Level0::~Level0(){
    delete level_;
}

void Level0::setNextBlockType(){
    if (level_->blockIndex_ == -1){
        level_->nextBlockType_ = OBlock;
    }

    level_->nextBlockType_ = level_->blockList_.at(level_->blockIndex_);
    updateBlockIndex();
}
