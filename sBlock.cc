#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'S';
    createBlock({{1,3}, {2,3}, {0,4}, {1,4}}, board);

}

OBlock::~OBlock() {}
