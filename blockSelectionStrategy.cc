#include "blockSelectionStrategy.h"
#include "block.h"

using namespace std;

// BlockSelectionStrategy::BlockSelectionStrategy(){}

// // Constructor
// BlockSelectionStrategy::BlockSelectionStrategy(BlockFactory* bf){
//     //blockFactory_ = bf;
// }

// Destructor
BlockSelectionStrategy::~BlockSelectionStrategy(){}

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

void BlockSelectionStrategy::setRandom(bool){}
void BlockSelectionStrategy::setSequenceFile(string){}