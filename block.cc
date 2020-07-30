#include "block.h"
#include "tile.h"
#include <vector>

Block::Block() {}
Block::~Block() {}

// Private methods to check if block can move left

// TODO: The xy mapping to ij is wrong

bool Block::canMoveLeft(Board* board) {

    for (auto tile: tiles_) {
        if (tile->getXCoordinate() == 0 || !board->getTileAt_(tile->getXCoordinate() - 1, tile->getYCoordinate())->isFilled()) {
            return false;
        }
    }
    return true;
}

bool Block::canMoveRight(Board* board) {

    for (auto tile: tiles_) {
        if (tile->getXCoordinate() == 10 || !board->getTileAt_(tile->getXCoordinate() + 1, tile->getYCoordinate())->isFilled()) {
            return false;
        }
    }
    return true;
}

bool Block::canMoveDown(Board* board) {

    for (auto tile: tiles_) {
        if (tile->getYCoordinate() == 17 || !board->getTileAt_(tile->getXCoordinate(), tile->getYCoordinate() + 1)->isFilled()) {
            return false;
        }
    }
    return true;
}

void Block::moveLeft(Board* board) {

    if (!canMoveLeft(board)) { return; }

    std::vector<Tile*> tempTiles_;

    // Clear current location of block
    for(auto tile: tiles_) {
        tile->setTileValue(' ');
        tempTiles_.push_back(board->getTileAt_(tile->getXCoordinate() - 1, tile->getYCoordinate()));
    }

    // Populate new locations for the block with the block type
    for (auto tile: tempTiles_) {
        tile->setTileValue(type);
    }

    tiles_.clear();
    tiles_ = tempTiles_;

}

void Block::moveRight(Board* board) {

    if (!canMoveRight(board)) { return; }

    std::vector<Tile*> tempTiles_;

    // Clear current location of block
    for(auto tile: tiles_) {
        tile->setTileValue(' ');
        tempTiles_.push_back(board->getTileAt_(tile->getXCoordinate() + 1, tile->getYCoordinate()));
    }

    // Populate new locations for the block with the block type
    for (auto tile: tempTiles_) {
        tile->setTileValue(type);
    }

    tiles_.clear();
    tiles_ = tempTiles_;

}

void Block::moveDown(Board* board) {

    if (!canMoveDown(board)) { return; }

    std::vector<Tile*> tempTiles_;

    // Clear current location of block
    for(auto tile: tiles_) {
        tile->setTileValue(' ');
        tempTiles_.push_back(board->getTileAt_(tile->getXCoordinate(), tile->getYCoordinate() + 1));
    }

    // Populate new locations for the block with the block type
    for (auto tile: tempTiles_) {
        tile->setTileValue(type);
    }

    tiles_.clear();
    tiles_ = tempTiles_;

}
