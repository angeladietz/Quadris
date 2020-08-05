#include "block.h"
#include "board.h"
#include "tile.h"
#include <exception>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

Block::Block() {}

Block::~Block() {
    for (auto tile: tiles_){
        tile->reset();
    }
}

void Block::createBlock(std::vector<std::vector<int>> locations, Board* board) {
    if (!canCreateBlock(locations, board)){
        board->endGame();
		return;
    }

    for (auto location: locations) {
        Tile* blockTile = board->getTileAt(location[0], location[1]);
        blockTile->setTileValue(type);
		    blockTile->setBlock(this);
        tiles_.push_back(blockTile);
    }
}

bool Block::canCreateBlock(vector<vector<int>> locations, Board* board){
    for (auto location: locations) {
        Tile* blockTile = board->getTileAt(location[0], location[1]);
        if (blockTile->isFilled()){
            return false;
        }
    }
    return true;
}

// Private methods to check if block can move left

BlockType Block::getBlockType() const{
    return blocktype;
}

bool Block::canMove(Board* board, std::vector<int> dir) {

    std::vector<Tile*> tempTiles_;
    for (auto tile: tiles_) {
        int newX = tile->getXCoordinate() + dir[0];
        int newY = tile->getYCoordinate() + dir[1];
        if (newX < 0 || newX > 10 || newY < 0 || newY > 17) {
		return false;
        }
        tempTiles_.push_back(board->getTileAt(newX, newY));
    }
    bool filledByCurrentTile = false;
    for (auto newTile: tempTiles_) {
	    filledByCurrentTile = false;
        if (board->getTileAt(newTile->getXCoordinate(), newTile->getYCoordinate())->isFilled()) {
		    for (auto tile: tiles_) {
				if (newTile->getXCoordinate() == tile->getXCoordinate() && newTile->getYCoordinate() == tile->getYCoordinate()) {
    	            // There's a tile in the current block that exists at the same location
    	        	filledByCurrentTile = true;
				}
			}
			if (!filledByCurrentTile) {
			    return false;
			}
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
        tile->reset();
        tempTiles_.push_back(board->getTileAt(tile->getXCoordinate()-1, tile->getYCoordinate()));
    }

    // Populate new locations for the block with the block type
    for (auto tile: tempTiles_) {
        tile->setTileValue(type);
		tile->setBlock(this);
    }

    tiles_.clear();
    tiles_ = tempTiles_;

}

void Block::moveRight(Board* board) {

    if (!canMoveRight(board)) { return; }

    std::vector<Tile*> tempTiles_;

    // Clear current location of block
    for(auto tile: tiles_) {
        tile->reset();
        tempTiles_.push_back(board->getTileAt(tile->getXCoordinate() + 1, tile->getYCoordinate()));
    }

    // Populate new locations for the block with the block type
    for (auto tile: tempTiles_) {
        tile->setTileValue(type);
		    tile->setBlock(this);
    }

    tiles_.clear();
    tiles_ = tempTiles_;

}

void Block::moveDown(Board* board) {

    if (!canMoveDown(board)) { return; }

    std::vector<Tile*> tempTiles_;

    // Clear current location of block
    for(auto tile: tiles_) {
        tile->reset();
        tempTiles_.push_back(board->getTileAt(tile->getXCoordinate(), tile->getYCoordinate()+1));
    }

    // Populate new locations for the block with the block type
    for (auto tile: tempTiles_) {
        tile->setTileValue(type);
		tile->setBlock(this);
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

    if (!canRotateClockwise(board)) { return; }

    std::vector<int> endPoints = getEndCoordinates();
    std::vector<Tile*> tempTiles_;

    // Find the new tiles
    for (auto tile:tiles_) {
       int newX = tile->getXCoordinate() - (tile->getXCoordinate() - endPoints[0]) + (endPoints[3] - tile->getYCoordinate());
       int newY = tile->getYCoordinate() + (tile->getXCoordinate() - endPoints[1]) + (endPoints[3] - tile->getYCoordinate());
       tempTiles_.push_back(board->getTileAt(newX, newY));
    }

    // Clear old tiles
    for (auto tile:tiles_) {
        tile->reset();
    }

    // Set new tiles
    for (auto tile:tempTiles_) {
        tile->setTileValue(type);
		tile->setBlock(this);
    }
    
    // Clear previous tiles, copy over new tiles
    tiles_.clear();
    tiles_ = tempTiles_;
}

void Block::rotateCounterClockwise(Board* board) {

    if (!canRotateCounterClockwise(board)) { return; }

    std::vector<int> endPoints = getEndCoordinates();
    std::vector<Tile*> tempTiles_;

    // Find the new tiles
    for (auto tile:tiles_) {
       int newX = tile->getXCoordinate() - (tile->getXCoordinate() - endPoints[0]) - (endPoints[2] - tile->getYCoordinate());
       int newY = tile->getYCoordinate() - (tile->getXCoordinate() - endPoints[0]) + (endPoints[3] - tile->getYCoordinate());
       tempTiles_.push_back(board->getTileAt(newX, newY));
    }

    // Clear old tiles
    for (auto tile:tiles_) {
        tile->reset();
    }

    // Set new tiles
    for (auto tile:tempTiles_) {
        tile->setTileValue(type);
		tile->setBlock(this);
    }
    
    // Clear previous tiles, copy over new tiles
    tiles_.clear();
    tiles_ = tempTiles_;
}

bool Block::canRotateClockwise(Board* board) {

    std::vector<Tile*> tempTiles_;
    std::vector<int> endPoints = getEndCoordinates();
    // Check that each new tile is in bounds
    for (auto tile:tiles_) {
       int newX = tile->getXCoordinate() - (tile->getXCoordinate() - endPoints[0]) + (endPoints[3] - tile->getYCoordinate());
       int newY = tile->getYCoordinate() + (tile->getXCoordinate() - endPoints[1]) + (endPoints[3] - tile->getYCoordinate());
        if (newX < 0 || newX > 10 || newY < 0 || newY > 17){
            return false;
        }
        tempTiles_.push_back(board->getTileAt(newX, newY));
    }

    bool filledByCurrentTile = false;
    for (auto newTile: tempTiles_) {
        if (board->getTileAt(newTile->getXCoordinate(), newTile->getYCoordinate())->isFilled()) {
            for (auto tile: tiles_) {
               if (newTile->getXCoordinate() == tile->getXCoordinate() && newTile->getYCoordinate() == tile->getYCoordinate()) {
                    // There's a tile in the current block that exists at the same location
                    filledByCurrentTile = true;
               } 
            }
            if (!filledByCurrentTile) {
                return false;
            }
        }
    }
    return true;
}

bool Block::canRotateCounterClockwise(Board* board) {

    std::vector<Tile*> tempTiles_;
    std::vector<int> endPoints = getEndCoordinates();

    // Check that each new tile is in bounds
    for (auto tile:tiles_) {
       int newX = tile->getXCoordinate() - (tile->getXCoordinate() - endPoints[0]) - (endPoints[2] - tile->getYCoordinate());
       int newY = tile->getYCoordinate() - (tile->getXCoordinate() - endPoints[0]) + (endPoints[3] - tile->getYCoordinate());
        if (newX < 0 || newX > 10 || newY < 0 || newY >= 17){
            return false;
        }
        tempTiles_.push_back(board->getTileAt(newX, newY));
    }

    bool filledByCurrentTile = false;
    for (auto newTile: tempTiles_) {
        if (board->getTileAt(newTile->getXCoordinate(), newTile->getYCoordinate())->isFilled()) {
            for (auto tile: tiles_) {
               if (newTile->getXCoordinate() == tile->getXCoordinate() && newTile->getYCoordinate() == tile->getYCoordinate()) {
                    // There's a tile in the current block that exists at the same location
                    filledByCurrentTile = true;
               } 
            }
            if (!filledByCurrentTile) {
                return false;
            }
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
	  tileBelow->setBlock(oldTile->getBlock());

    //clear the old tile value and remove it from the block
    oldTile->reset();
    removeTile(oldTile);

    //Add the new tile to the block
    tiles_.push_back(tileBelow);
}

vector<vector<int>> Block::getCurrentCoordinates() {
    vector<vector<int>> locations;
    for (auto tile: tiles_) {
        locations.push_back({tile->getXCoordinate(), tile->getYCoordinate()});
    }
    return locations;
}

void Block::resetToLocations(Board* board, std::vector<std::vector<int>> locations, bool finalReset) {
    
    std::vector<Tile*> tempTiles_;
    int index = 0;

    // Clear current location of block
    for(auto tile: tiles_) {
        tile->reset();
        tempTiles_.push_back(board->getTileAt(locations[index][0], locations[index][1]));
        index++;
    }

    if (finalReset) {
    // Populate new locations for the block with the block type
        for (auto tile: tempTiles_) {
            tile->setTileValue(type);
            tile->setBlock(this);
        }
    }

    tiles_.clear();
    tiles_ = tempTiles_;
}

vector<vector<int>> Block::getBlockHint(Board* board) {
    int lowestY = 0;
    vector<vector<int>> original_locations, current_locations, hint_location;
    // Store current tile locations
    original_locations = getCurrentCoordinates();
    // Check all locations on the right that block can be dropped at
    while (canMoveRight(board)) {
        current_locations = getCurrentCoordinates();
        while (canMoveDown(board)) {
            moveDown(board);
        }
        vector<int> endPoints = getEndCoordinates();
        if (endPoints[3] > lowestY) {
            lowestY = endPoints[3];
            hint_location = getCurrentCoordinates();
        }
        resetToLocations(board, current_locations);
        current_locations = getCurrentCoordinates();
        moveRight(board);
    }
    while (canMoveLeft(board)) {
        current_locations = getCurrentCoordinates();
        while (canMoveDown(board)) {
            moveDown(board);
        }
        vector<int> endPoints = getEndCoordinates();
        if (endPoints[3] > lowestY) {
            lowestY = endPoints[3];
            hint_location = getCurrentCoordinates();
        }
        resetToLocations(board, current_locations);
        moveLeft(board);
    }
    resetToLocations(board, original_locations, true);
    return hint_location;
}
