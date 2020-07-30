#include "block.h"
#include "tile.h"
#include <utility>
#include <vector>
#include <algorithm>

Block::Block() {}
Block::~Block() {}

// Private methods to check if block can move left

// TODO: The xy mapping to ij is wrong

bool Block::canMove(Board* board, std::vector<int> dir) {

    for (auto tile: tiles_) {
        if (tile->getXCoordinate() + dir[0] < 0 || tile->getXCoordinate() + dir[0] > 10 || tile->getYCoordinate() + dir[1] == 17 || \
                !board->getTileAt_(tile->getXCoordinate() + dir[0], tile->getYCoordinate() + dir[1])->isFilled()) {
            return false;
        }
    }
    return true;
}

bool Block::canMoveLeft(Board* board) {
    return canMove(board, {-1, 0});
}

bool Block::canMoveRight(Board* board) {
    return canMove(board, {1, 0});
}

bool Block::canMoveDown(Board* board) {
    return canMove(board, {0, 1});
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

std::vector<int> Block::getEndCoordinates() {

    std::vector<int> x_coordinates, y_coordinates;

    for (auto tile: tiles_) {
        x_coordinates.push_back(tile->getXCoordinate());
        y_coordinates.push_back(tile->getYCoordinate());
    }
    auto x = std::minmax_element(x_coordinates.begin(), x_coordinates.end());
    auto y = std::minmax_element(y_coordinates.begin(), y_coordinates.end());
    return { *x.first, *x.second, *y.first, *y.second };
}

void Block::rotateClockwise(Board* board) {
    std::vector<int> endPoints = getEndCoordinates();
    std::vector<Tile*> tempTiles_;

    // Find the new tiles
    for (auto tile:tiles_) {
       tempTiles_.push_back(board->getTileAt_(tile->getXCoordinate(), tile->getYCoordinate()));
    }

    // Clear old tiles
    for (auto tile:tiles_) {
        tile->setTileValue(' ');
    }

    // Set new tiles
    for (auto tile:tempTiles_) {
        tile->setTileValue(type);
    }
    
    // Clear previous tiles, copy over new tiles
    tiles_.clear();
    tiles_ = tempTiles_;
}

void Block::rotateCounterClockwise(Board* board) {
    std::vector<int> endPoints = getEndCoordinates();
    std::vector<Tile*> tempTiles_;

    // Find the new tiles
    for (auto tile:tiles_) {
       tempTiles_.push_back(board->getTileAt_(tile->getXCoordinate(), tile->getYCoordinate()));
    }

    // Clear old tiles
    for (auto tile:tiles_) {
        tile->setTileValue(' ');
    }

    // Set new tiles
    for (auto tile:tempTiles_) {
        tile->setTileValue(type);
    }
    
    // Clear previous tiles, copy over new tiles
    tiles_.clear();
    tiles_ = tempTiles_;
}
