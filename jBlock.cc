#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'J';
    createBlock({{0,3}, {0,4}, {1,4}, {2,4}}, board);

}

OBlock::~OBlock() {}
