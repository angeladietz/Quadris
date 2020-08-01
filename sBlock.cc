#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'S';
    createBlock({{1,3}, {2,3}, {0,4}, {1,4}}, board);

}

OBlock::~OBlock() {}

//Undefined since rotation of O Blocks is meaningless
void OBlock::rotateClockwise() {}
void OBlock::rotateCounterClockwise() {}
