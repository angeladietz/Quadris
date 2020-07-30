#include "oBlock.h"

OBlock::OBlock(Board *board) {
   
    // Initialize the block at the right locations of the board
    tiles_.push_back(board->getTileAt_(0, 3));
    tiles_.push_back(board->getTileAt_(0, 4));
    tiles_.push_back(board->getTileAt_(1, 3));
    tiles_.push_back(board->getTileAt_(0, 4));

    // TODO: Do I need to check if there is a block already there or will that be handled by game controller?

    for (auto tile: tiles_) {
        tile->setTileValue(type);
    }

}

OBlock::~OBlock() {}

void OBlock::rotateClockwise() {}
void OBlock::rotateCounterClockwise() {}
