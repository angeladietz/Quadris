#include "board.h"
#include "block.h"
#include "tile.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "blockFactory.h"
#include <vector>

using namespace std;

// Constructor
Board::Board(int startLevel, string l0ScriptFile){
    board_ = new PImpl_B;
    initGrid();
    board_->curScore_ = 0;
    board_->blockFactory_ = new BlockFactory();
    board_->curLevel_ = startLevel;
    board_->L0SeqFile_ = l0ScriptFile;
    initBlockSelector();
    board_->curBlock_ = board_->blockSelectionStrategy_->getNextBlock();
}

void Board::initGrid(){
    for (int i = 0; i < BOARD_HEIGHT; i++){
        board_->grid_.push_back(vector<Tile*>(BOARD_WIDTH, nullptr));
    }
}

void Board::initBlockSelector(){
    switch (board_->curLevel_){
        case 0:
            board_->blockSelectionStrategy_ = new Level0(board_->blockFactory_, board_->L0SeqFile_);
            break;
        case 1:
            board_->blockSelectionStrategy_ = new Level1(board_->blockFactory_);
            break;
        case 2:
            board_->blockSelectionStrategy_ = new Level2(board_->blockFactory_);
            break;
        case 3:
            board_->blockSelectionStrategy_ = new Level3(board_->blockFactory_);
            break;
        case 4:
            board_->blockSelectionStrategy_ = new Level4(board_->blockFactory_);
            break;
    }
}

//Destructor
Board::~Board(){
    if (nullptr != board_){
        if (board_->curBlock_ != nullptr){
            delete board_->curBlock_;
        }
        if (board_->nextBlock_ != nullptr){
            delete board_->nextBlock_;
        }
        deleteGrid();
        delete board_->blockSelectionStrategy_;
        delete board_->blockFactory_;
    }
    delete board_;
}

// Helper function for destructor to delete the grid
void Board::deleteGrid(){
    //TODO: DEPENDING ON IMPLEMENTATION, MAY NEED TO DELETE OTHER BLOCKS AS WELL
    if (board_ != nullptr){
        for (int i = 0; i < BOARD_HEIGHT; i++){
            for (int j = 0; j < BOARD_WIDTH; j++){
                if (board_->grid_[i][j]!= nullptr){
                    delete board_->grid_[i][j];
                }
            }
        }
    }
}

Tile* Board::getTileAt(int x, int y){
    return board_->grid_[x][y];
}

void Board::moveCurBlockLeft(){
    board_->curBlock_->moveLeft(this);
}

void Board::moveCurBlockRight(){
    board_->curBlock_->moveRight(this);
}

void Board::moveCurBlockDown(){
    board_->curBlock_->moveDown(this);
}

void Board::rotateCurBlockClockwise(){
    board_->curBlock_->rotateClockwise(this);
}

void Board::rotateCurBlockCounterClockwise(){
    board_->curBlock_->rotateCounterClockwise(this);
}

void Board::dropCurBlock(){
    board_->curBlock_->dropBlock();
    checkForFullRow();
}

void Board::checkForFullRow(){
    int numRowsFilled = 0;

    // Go through board and check for any full rows, and clear
    // them if there are any
    // Start at row 3 since the first 3 rows are extra space
    for (int i = 3; i < BOARD_HEIGHT; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            if (!board_->grid_[i][j]->isFilled()){
                break;
            }
            else if (j == BOARD_WIDTH-1){
                // Row is full
                clearRow(i);
                numRowsFilled++;
            }
        }
    }
    updateScore(getPointsFromClearedRows(numRowsFilled));
}

void Board::clearRow(int rowNum){
    for (int i = 0; i < BOARD_WIDTH; i++){
        if (board_->grid_[rowNum][i]->isLastTileFromBlock()){
            updateScore(getPointsFromClearedBlock());
        }
        board_->grid_[rowNum][i]->deleteTileFromRow();
    }
    moveRowsDownOneRow(rowNum);
}

void Board::moveRowsDownOneRow(int rowNum){
    for (int i = rowNum-1; i >=3; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            board_->grid_[i][j]->moveDownOneRow(this);
        }
    }
}

int Board::getPointsFromClearedBlock(){
    return (board_->curLevel_ + 1)*(board_->curLevel_ + 1);
}

int Board::getPointsFromClearedRows(int numRowsCleared){
    int sqrtScoredPoints = board_->curLevel_ + numRowsCleared;
    int scoredPoints = sqrtScoredPoints*sqrtScoredPoints;
    return scoredPoints;
}

void Board::updateScore(int points){
    board_->curScore_ += points;
}

// Increases the level of the game by one
void Board::levelUp(){
    if (board_->curLevel_ < MAX_LEVEL){
        delete board_->blockSelectionStrategy_;
    }
    board_->curLevel_++;
    initBlockSelector();
}

// Decreases the level of the game by one
void Board::levelDown(){
    if (board_->curLevel_ > MIN_LEVEL){
        delete board_->blockSelectionStrategy_;
    }
    board_->curLevel_--;
    initBlockSelector();
}

// Sets the current block to be of type bType
void Board::setCurBlock(BlockType bType){
    if (board_->curBlock_->getBlockType() != bType){
        delete board_->curBlock_;
        board_->curBlock_ = board_->blockSelectionStrategy_->getBlockOfType(bType);
    }
}

void Board::setNoRand(std::string filename){
    if (board_->curLevel_ == 3 || board_->curLevel_ == 4){
        board_->blockSelectionStrategy_->setRandom(false);
        board_->blockSelectionStrategy_->setSequenceFile(filename);
        board_->isRandom_ = false;
        board_->noRandFile_ = filename;
    }
}

void Board::setRand(){
    if (board_->curLevel_ == 3 || board_->curLevel_ == 4){
        board_->blockSelectionStrategy_->setRandom(true);
        board_->isRandom_ = true;
    }
}
