#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    type = 'O';
    createBlock({{0,3}, {1,3}, {0,4}, {1,4}}, board);

}

OBlock::~OBlock() {}
