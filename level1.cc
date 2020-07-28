#include "level1.h"
#include "blockSelectionStrategy.h"
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

// Default onstructor
Level1::Level1(){
    level1_ = new PImpl_l1;
    setBlockProbabilities();
    areBlocksHeavy_ = false;
}

void Level1::setBlockProbabilities(){
    level1_->blockProbabilities_[SBlock] = 1.0/12;
    level1_->blockProbabilities_[ZBlock] = 1.0/12;
    level1_->blockProbabilities_[IBlock] = 1.0/6;
    level1_->blockProbabilities_[JBlock] = 1.0/6;
    level1_->blockProbabilities_[LBlock] = 1.0/6;
    level1_->blockProbabilities_[OBlock] = 1.0/6;
    level1_->blockProbabilities_[TBlock] = 1.0/6;
}

// Destructor
Level1::~Level1(){
    delete level1_;
}

Block* Level1::getNextBlock(){
    BlockType type = getNextBlockType();
    return blockFactory_->createBlock(type, areBlocksHeavy_);
}

BlockType Level1::getNextBlockType(){
    int weightSum = 1;

    // get a random number between 1 and 1000
    int rand = std::rand() % 1000;

    // get random number between 0 and 1 with 3 decimal digits
    rand /= 1000.0;

    for (auto const& it : level1_->blockProbabilities_) {
        rand -= it.second;
        if (rand <= 0){
            return it.first;
        }
    }
}