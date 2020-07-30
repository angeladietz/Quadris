#include "board.h"
#include "block.h"
#include "tile.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include <vector>

using namespace std;

// Constructor
Board::Board(int startLevel, string l0ScriptFile){
    board_ = new PImpl_B;
    initGrid();
    board_->curScore_ = 0;
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
            board_->blockSelectionStrategy_ = new Level0(board_->L0SeqFile_);
            break;
        case 1:
            board_->blockSelectionStrategy_ = new Level1();
            break;
        case 2:
            board_->blockSelectionStrategy_ = new Level2();
            break;
        case 3:
            board_->blockSelectionStrategy_ = new Level3();
            break;
        case 4:
            board_->blockSelectionStrategy_ = new Level4();
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

void Board::moveCurBlockLeft(){

}

void Board::moveCurBlockRight(){

}

void Board::moveCurBlockDown(){

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
        //TODO
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
