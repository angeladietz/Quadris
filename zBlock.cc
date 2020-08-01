#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'Z';
    createBlock({{0,3}, {1,3}, {1,4}, {2,4}}, board);

}

OBlock::~OBlock() {}
