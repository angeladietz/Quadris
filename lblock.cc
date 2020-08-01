#include "lBlock.h"
#include "board.h"

LBlock::LBlock(Board *board) {

		type = 'L';
    createBlock({{2,3}, {0,4}, {1,4}, {2,4}}, board);

}

LBlock::~LBlock() {}

void LBlock::rotateClockwise() {

}

void LBlock::rotateCounterClockwise() {

}
