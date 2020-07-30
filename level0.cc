#include "level0.h"
#include "blockSelectionStrategy.h"
#include <fstream>

using namespace std;

// Constructor
Level0::Level0(string filename = "sequence.txt"){
    level0_ = new PImpl_L0;
    level0_->areBlocksHeavy_ = false;

    ifstream blockFile;

    //TODO: ADD EXCEPTION HANDLING!
    blockFile.open(filename);

    if (blockFile.is_open()){

        char nextBlock;
        while(blockFile>>nextBlock){
            BlockType bType = getBlockType(nextBlock);
            if (bType != INVALID_BLOCK){
                level0_->blockList_.emplace(bType);
            }
        }
        blockFile.close();
    }
}

// Destructor
Level0::~Level0(){
    delete level0_;
}

Block* Level0::getNextBlock(){
    BlockType type = getNextBlockType();
    return level0_->blockFactory_->createBlock(type, level0_->areBlocksHeavy_);
}

BlockType Level0::getNextBlockType(){
    BlockType bType = level0_->blockList_.front();
    level0_->blockList_.pop();
    return bType;
}