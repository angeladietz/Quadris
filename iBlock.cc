#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'I';
    createBlock({{0,3}, {1,3}, {2,3}, {3,3}}, board);

}

OBlock::~OBlock() {}
