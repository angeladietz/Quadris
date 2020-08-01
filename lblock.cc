#include "lBlock.h"
#include "block.h"

LBlock::LBlock(Board *board) {

		type = 'L';
    blocktype = BlockType::LBlock;
    createBlock({{2,3}, {0,4}, {1,4}, {2,4}}, board);

}

LBlock::~LBlock() {}
