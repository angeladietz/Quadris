#include "lBlock.h"
#include "board.h"

LBlock::LBlock(Board *board) {

    // Initialize the block at the right location
    tiles_.push_back(board->getTileAt_(2, 3));
    tiles_.push_back(board->getTileAt_(0, 4));
    tiles_.push_back(board->getTileAt_(1, 4));
    tiles_.push_back(board->getTileAt_(2, 4));

    // Update the tiles with the right value
    for (auto tile: tiles_) {
        tile->setTileValue(type);
    }

}

LBlock::~LBlock() {}

void LBlock::rotateClockwise() {

}

void LBlock::rotateCounterClockwise() {

}
