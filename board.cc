#include "board.h"
#include "block.h"
#include "blockFactory.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "quadris.h"
#include "tile.h"
#include <ostream>
#include <vector>

using namespace std;

// Constructor
Board::Board(Quadris *quadris, int startLevel, string l0ScriptFile) {
  board_ = new PImpl_B;
  board_->quadris_ = quadris;
  initGrid();
  board_->curScore_ = 0;
  board_->highScore_ = highScore;
  board_->blockFactory_ = new BlockFactory(this);
  board_->curLevel_ = startLevel;
  board_->L0SeqFile_ = l0ScriptFile;
  board_->isRandom_ = true;
  board_->isHintSet_ = false;
  initBlockSelector();
  initBlocks();
  board_->blockCount_ = 0;
  board_->isGameOver_ = false;
}

void Board::initGrid() {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    board_->grid_.push_back(vector<Tile *>(BOARD_WIDTH, nullptr));
    for (int j = 0; j < BOARD_WIDTH; j++) {
      board_->grid_[i][j] = new Tile(j, i);
    }
  }
}

void Board::initBlockSelector() {
  switch (board_->curLevel_) {
  case 0:
    board_->blockSelectionStrategy_ =
        new Level0(board_->blockFactory_, board_->L0SeqFile_);
    break;
  case 1:
    board_->blockSelectionStrategy_ = new Level1(board_->blockFactory_);
    break;
  case 2:
    board_->blockSelectionStrategy_ = new Level2(board_->blockFactory_);
    break;
  case 3:
    board_->blockSelectionStrategy_ =
        new Level3(board_->blockFactory_, board_->isRandom_);
    if (!board_->isRandom_) {
      board_->blockSelectionStrategy_->setSequenceFile(board_->noRandFile_);
    }
    break;
  case 4:
    board_->blockSelectionStrategy_ =
        new Level4(board_->blockFactory_, board_->isRandom_);
    if (!board_->isRandom_) {
      board_->blockSelectionStrategy_->setSequenceFile(board_->noRandFile_);
    }
    break;
  }
}

void Board::initBlocks() {
  board_->curBlock_ = board_->blockSelectionStrategy_->getNextBlock();
  board_->nextBlockType_ = board_->blockSelectionStrategy_->getNextBlockType();
}

// Destructor
Board::~Board() {
  if (board_->blockSelectionStrategy_ != nullptr) {
    delete board_->blockSelectionStrategy_;
  }
  if (board_->blockFactory_ != nullptr) {
    delete board_->blockFactory_;
  }
  if (nullptr != board_) {
    if (board_->curBlock_ != nullptr) {
      delete board_->curBlock_;
    }
  }
  deleteGrid();
  delete board_;
}

// Helper function for destructor to delete the grid
void Board::deleteGrid() {
  if (board_ != nullptr) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
      for (int j = 0; j < BOARD_WIDTH; j++) {
        if (board_->grid_[i][j] != nullptr) {
          delete board_->grid_[i][j];
        }
      }
    }
  }
}

Tile *Board::getTileAt(int x, int y) { return board_->grid_[y][x]; }

int Board::getScore() { return board_->curScore_; }

int Board::getLevel() { return board_->curLevel_; }

bool Board::getIsGameOver() { return board_->isGameOver_; }

BlockType Board::getNextBlockType() { return board_->nextBlockType_; }

void Board::moveCurBlockLeft() { board_->curBlock_->moveLeft(this); }

void Board::moveCurBlockRight() { board_->curBlock_->moveRight(this); }

void Board::moveCurBlockDown() { board_->curBlock_->moveDown(this); }

void Board::rotateCurBlockClockwise() {
  board_->curBlock_->rotateClockwise(this);
}

void Board::rotateCurBlockCounterClockwise() {
  board_->curBlock_->rotateCounterClockwise(this);
}

void Board::dropCurBlock() {
  board_->curBlock_->dropBlock(this);
  checkForFullRow();

  if (doesLevelDropTiles()) {
    board_->blockCount_++;
    if (board_->blockCount_ % 5 == 0) {
      dropTileBlock();
    }
  }
  setupNextBlocks();
}

void Board::checkForFullRow() {
  int numRowsFilled = 0;

  // Go through board and check for any full rows, and clear
  // them if there are any
  // Start at row 3 since the first 3 rows are extra space
  for (int i = 3; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (!board_->grid_[i][j]->isFilled()) {
        break;
      }
      if (j == BOARD_WIDTH - 1) {
        // Row is full
        clearRow(i);
        numRowsFilled++;
      }
    }
  }
  if (numRowsFilled != 0) {
    updateScore(getPointsFromClearedRows(numRowsFilled));
  }
}

void Board::clearRow(int rowNum) {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (board_->grid_[rowNum][i]->isLastTileFromBlock()) {
      updateScore(
          getPointsFromClearedBlock(board_->grid_[rowNum][i]->getBlock()));
    }
    board_->grid_[rowNum][i]->deleteFromBlock();
  }
  moveRowsDownOneRow(rowNum);
}

void Board::moveRowsDownOneRow(int rowNum) {
  for (int i = rowNum - 1; i >= 0; i--) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (board_->grid_[i][j]->isFilled()) {
        board_->grid_[i][j]->moveDownOneRow(this);
      }
    }
  }
}

int Board::getPointsFromClearedBlock(Block *block) {
  return (block->getGenLevel() + 1) * (block->getGenLevel() + 1);
}

int Board::getPointsFromClearedRows(int numRowsCleared) {
  if (numRowsCleared == 0) {
    return 0;
  }
  int sqrtScoredPoints = board_->curLevel_ + numRowsCleared;
  int scoredPoints = sqrtScoredPoints * sqrtScoredPoints;
  return scoredPoints;
}

void Board::updateScore(int points) {
  board_->curScore_ += points;
  highScore = max(highScore, board_->curScore_);
}

bool Board::doesLevelDropTiles() { return board_->curLevel_ == 4; }

void Board::dropTileBlock() {
  Block *tileBlock =
      board_->blockSelectionStrategy_->getBlockOfType(TILE_BLOCK);
  tileBlock->dropBlock(this);
  checkForFullRow();
}

void Board::setupNextBlocks() {
  board_->curBlock_ = board_->blockSelectionStrategy_->getNextBlock();
  if (!board_->isGameOver_) {
    board_->nextBlockType_ =
        board_->blockSelectionStrategy_->getNextBlockType();
  }
}

// Increases the level of the game by one
void Board::levelUp() {
  if (board_->curLevel_ < MAX_LEVEL) {
    delete board_->blockSelectionStrategy_;
    board_->curLevel_++;
    initBlockSelector();
  }
}

// Decreases the level of the game by one
void Board::levelDown() {
  if (board_->curLevel_ > MIN_LEVEL) {
    delete board_->blockSelectionStrategy_;
    board_->curLevel_--;
    initBlockSelector();
  }
}

// Sets the current block to be of type bType
void Board::setCurBlock(BlockType bType) {
  delete board_->curBlock_;
  board_->curBlock_ = board_->blockSelectionStrategy_->getBlockOfType(bType);
}

void Board::setNoRand(std::string filename) {
  if (board_->curLevel_ == 3 || board_->curLevel_ == 4) {
    board_->blockSelectionStrategy_->setRandom(false);
    board_->blockSelectionStrategy_->setSequenceFile(filename);
    board_->isRandom_ = false;
    board_->noRandFile_ = filename;
  }
}

void Board::setRand() {
  if (board_->curLevel_ == 3 || board_->curLevel_ == 4) {
    board_->blockSelectionStrategy_->setRandom(true);
    board_->isRandom_ = true;
  }
}

void Board::moveDownHeavyBlock() {
  if (board_->curBlock_->isHeavy()) {
    board_->curBlock_->moveDown(this);
  }
}

void Board::restart() { board_->quadris_->restartGame(); }

void Board::endGame() {
  board_->isGameOver_ = true;
  notifyObservers();
}

bool Board::isHintSet() { return board_->isHintSet_; }

void Board::drawHint() {
  for (auto loc : board_->hintLocations_) {
    Tile *currTile = getTileAt(loc[0], loc[1]);
    currTile->setTileValue('?');
  }
  board_->isHintSet_ = true;
}

void Board::clearHint() {
  for (auto loc : board_->hintLocations_) {
    Tile *currTile = getTileAt(loc[0], loc[1]);
    currTile->reset();
  }
  board_->isHintSet_ = false;
  board_->hintLocations_.clear();
}

void Board::showHint() {
  board_->hintLocations_ = board_->curBlock_->getBlockHint(this);
  drawHint();
}

std::ostream &operator<<(ostream &out, Board &board) {

  for (int row = 0; row < BOARD_HEIGHT; row++) {
    out << row + 1 << "	";
    for (auto col : board.board_->grid_[row]) {
      out << *col;
    }
    out << std::endl;
  }
  return out;
}
