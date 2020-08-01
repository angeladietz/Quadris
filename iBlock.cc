#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'I';
    createBlock({{0,3}, {1,3}, {2,3}, {3,3}}, board);

}

OBlock::~OBlock() {}

//Undefined since rotation of O Blocks is meaningless
void OBlock::rotateClockwise() {}
void OBlock::rotateCounterClockwise() {}
