#include "block.h"
#include "board.h"
#include "tile.h"
#include <utility>
#include <vector>
#include <algorithm>

Block::Block(BlockType blocktype, Board* board) {
    
    std::vector<std::vector<int>> locations;
    // Specify the locations for each block type
    if (blocktype == BlockType::IBlock) {
        locations = {{0,3}, {1,3}, {2,3}, {3,3}};
        type = 'I';
    } else if (blocktype == BlockType::JBlock) {
        locations = {{0,3}, {0,4}, {1,4}, {2,4}};
        type = 'J';
    } else if (blocktype == BlockType::LBlock) {
        locations = {{2,3}, {0,4}, {1,4}, {2,4}};
        type = 'L';
    } else if (blocktype == BlockType::OBlock) {
        locations = {{0,3}, {1,3}, {0,4}, {1,4}};
        type = 'O';
    } else if (blocktype == BlockType::SBlock) {
        locations = {{1,3}, {2,3}, {0,4}, {1,4}};
        type = 'S';
    } else if (blocktype == BlockType::ZBlock) {
        locations = {{0,3}, {1,3}, {1,4}, {2,4}};
        type = 'Z';
    } else if (blocktype == BlockType::TBlock) {
        locations = {{0,3}, {1,3}, {2,3}, {1,4}};
        type = 'T';
    } else {
        // Invalid block type
        // TODO: Need to handle case better
    }

    // Create block with the specified locations
    for (auto location: locations) {
        Tile* blockTile = board->getTileAt_(location[0], location[1]);
        blockTile->setTileValue(type);
        tiles_.push_back(blockTile);
    }
}

Block::~Block() {}

// Private methods to check if block can move left

// TODO: The xy mapping to ij is wrong
// TODO: Change all places where char is used to BlockType

BlockType Block::getBlockType() const{

    //return type;
}

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
       tempTiles_.push_back(board->getTileAt_(newX, newY));
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
       tempTiles_.push_back(board->getTileAt_(newX, newY));
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
        if (newX < 0 || newX > 10 || newY >= 17 || !board->getTileAt_(newX, newY)->isFilled()){
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
        if (newX < 0 || newX > 10 || newY >= 17 || !board->getTileAt_(newX, newY)->isFilled()){
            return false;
        }
    }
    return true;
}
