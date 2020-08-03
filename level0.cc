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

    setSequenceFile(filename);

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
    level_->nextBlockType_ = getNextNonRandBlockType();
}
