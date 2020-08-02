#include "tile.h"
#include "location.h"
#include "block.h"

using namespace std;

Tile::Tile(int x, int y, char tile) : location_(x, y) {
   tileValue_ = tile;
   block_ = nullptr;
}

Tile::~Tile(){
    if (block_ != nullptr && isLastTileFromBlock()){
        delete block_;
    }
}

bool Tile::isFilled() const {
    return tileValue_ == ' ';
}

char Tile::getTileValue() const {
    return tileValue_;
}

void Tile::setTileValue(const char tile) {
    tileValue_ = tile;
}

Block* Tile::getBlock(){
    return block_;
}

int Tile::getXCoordinate(){
    return location_.getX();
}

int Tile::getYCoordinate(){
    return location_.getY();
}

void Tile::setBlock(Block* block){
    block_ = block;
}

bool Tile::isLastTileFromBlock(){
    if (block_->getNumTiles() == 1){
        return true;
    }
    return false;
}

void Tile::deleteFromBlock(){
    block_->removeTile(this);
    reset();
}

void Tile::moveDownOneRow(Board* board){
    block_->moveTileDown(this, board);
}

void Tile::reset(){
    setTileValue(' ');
    block_ = nullptr;
}

std::ostream& operator<< (std::ostream& out, Tile& tile) {

		out << tile.getTileValue();
    return out;

}
