#include "block.h"
#include "board.h"
#include "tile.h"
#include <utility>
#include <vector>
#include <algorithm>

// TODO:
// getGenLevel
// heavy blocks

Block::Block() {}

void Block::createBlock(std::vector<std::vector<int>> locations, Board* board) {

    for (auto location: locations) {
        Tile* blockTile = board->getTileAt(location[0], location[1]);
        blockTile->setTileValue(type);
        tiles_.push_back(blockTile);
    }

    for (auto tile: tiles_) {
        tile->setTileValue(type);
    }

}

Block::~Block() {
    for (auto tile: tiles_){
        tile->reset();
    }
}

// Private methods to check if block can move left

// TODO: The xy mapping to ij is wrong
// TODO: Change all places where char is used to BlockType

BlockType Block::getBlockType() const{
    return blocktype;
}

bool Block::canMove(Board* board, std::vector<int> dir) {

    for (auto tile: tiles_) {
        if (tile->getXCoordinate() + dir[0] < 0 || tile->getXCoordinate() + dir[0] > 10 || tile->getYCoordinate() + dir[1] == 17 || \
                !board->getTileAt(tile->getXCoordinate() + dir[0], tile->getYCoordinate() + dir[1])->isFilled()) {
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
        tempTiles_.push_back(board->getTileAt(tile->getXCoordinate() - 1, tile->getYCoordinate()));
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
        tempTiles_.push_back(board->getTileAt(tile->getXCoordinate() + 1, tile->getYCoordinate()));
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
        tempTiles_.push_back(board->getTileAt(tile->getXCoordinate(), tile->getYCoordinate() + 1));
    }

    // Populate new locations for the block with the block type
    for (auto tile: tempTiles_) {
        tile->setTileValue(type);
    }

    tiles_.clear();
    tiles_ = tempTiles_;

}

void Block::dropBlock(Board* board){
    while (canMoveDown(board)){
        moveDown(board);
    }
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
       int newX = tile->getXCoordinate() - (tile->getXCoordinate() - endPoints[0]) + (endPoints[2] - tile->getYCoordinate());
       int newY = tile->getYCoordinate() + (tile->getXCoordinate() - endPoints[1]) + (endPoints[2] - tile->getYCoordinate());
       tempTiles_.push_back(board->getTileAt(newX, newY));
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
       int newX = tile->getXCoordinate() - (tile->getXCoordinate() - endPoints[0]) - (endPoints[2] - tile->getYCoordinate());
       int newY = tile->getYCoordinate() + (tile->getXCoordinate() - endPoints[1]) + (endPoints[3] - tile->getYCoordinate());
       tempTiles_.push_back(board->getTileAt(newX, newY));
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

bool Block::canRotateClockwise(Board* board) {
    std::vector<int> endPoints = getEndCoordinates();

    // Check that each new tile is in bounds
    for (auto tile:tiles_) {
       int newX = tile->getXCoordinate() - (tile->getXCoordinate() - endPoints[0]) + (endPoints[2] - tile->getYCoordinate());
       int newY = tile->getYCoordinate() + (tile->getXCoordinate() - endPoints[1]) + (endPoints[2] - tile->getYCoordinate());
        if (newX < 0 || newX > 10 || newY >= 17 || !board->getTileAt(newX, newY)->isFilled()){
            return false;
        }
    }
    return true;
}

bool Block::canRotateCounterClockwise(Board* board) {
    std::vector<int> endPoints = getEndCoordinates();

    // Check that each new tile is in bounds
    for (auto tile:tiles_) {
       int newX = tile->getXCoordinate() - (tile->getXCoordinate() - endPoints[0]) - (endPoints[2] - tile->getYCoordinate());
       int newY = tile->getYCoordinate() + (tile->getXCoordinate() - endPoints[1]) + (endPoints[3] - tile->getYCoordinate());
        if (newX < 0 || newX > 10 || newY >= 17 || !board->getTileAt(newX, newY)->isFilled()){
            return false;
        }
    }
    return true;
}

int Block::getNumTiles(){
    return tiles_.size();
}

int Block::getGenLevel(){
    return levelGen_;
}

bool Block::isHeavy(){
    return isHeavy_;
}

void Block::removeTile(Tile* tile){
    for (int i = 0; i < tiles_.size(); i++){
        if (tiles_[i] == tile){
            tiles_.erase(tiles_.begin() + i);
            return;
        }
    }
}

void Block::moveTileDown(Tile* oldTile, Board* board){
    //get the tile one row below and set its value to be that of the block
    Tile* tileBelow = board->getTileAt(oldTile->getXCoordinate(), oldTile->getYCoordinate() +1);
    tileBelow->setTileValue(type);

    //clear the old tile value and remove it from the block
    oldTile->setTileValue(' ');
    removeTile(oldTile);

    //Add the new tile to the block
    tiles_.push_back(tileBelow);
}
