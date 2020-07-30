#include "oBlock.h"
#include "board.h"

OBlock::OBlock(Board *board) {
   
    // Initialize the block at the right locations of the board
    tiles_.push_back(board->getTileAt(0, 3));
    tiles_.push_back(board->getTileAt(0, 4));
    tiles_.push_back(board->getTileAt(1, 3));
    tiles_.push_back(board->getTileAt(0, 4));

    // TODO: Do I need to check if there is a block already there or will that be handled by game controller?

    for (auto tile: tiles_) {
        tile->setTileValue(type);
    }

}

OBlock::~OBlock() {}

//Undefined since rotation of O Blocks is meaningless
void OBlock::rotateClockwise() {}
void OBlock::rotateCounterClockwise() {}
