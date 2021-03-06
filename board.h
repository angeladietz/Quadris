#ifndef _BOARD_
#define _BOARD_

#include <iostream>
#include <string>
#include <vector>

#include "block.h"
#include "blockFactory.h"
#include "blockSelectionStrategy.h"
#include "subject.h"
#include "tile.h"

#define MIN_LEVEL 0
#define MAX_LEVEL 4
#define BOARD_WIDTH 11
#define BOARD_HEIGHT 18

// Forward declaration of Quadris class
class Quadris;

// Private implementation for board class
struct PImpl_B {
  Block *curBlock_;
  BlockType nextBlockType_;
  std::vector<std::vector<Tile *>> grid_;
  int curLevel_;
  BlockSelectionStrategy *blockSelectionStrategy_;
  std::string L0SeqFile_;
  std::string noRandFile_;
  int curScore_;
  int highScore_;
  bool isRandom_;
  bool isHintSet_;
  std::vector<std::vector<int>> hintLocations_;
  int blockCount_;
  Quadris *quadris_;
  BlockFactory *blockFactory_;
  bool isGameOver_;
};

class Board : public Subject {
public:
  Board(Quadris *, int, std::string);
  ~Board();

  Tile *getTileAt(int, int);
  void moveCurBlockLeft();
  void moveCurBlockRight();
  void moveCurBlockDown();
  void rotateCurBlockCounterClockwise();
  void rotateCurBlockClockwise();
  void dropCurBlock();
  void levelUp();
  void levelDown();
  void setNoRand(std::string);
  void setRand();
  void setCurBlock(BlockType);
  void showHint();
  void clearHint();
  void restart();
  void endGame();
  void updateTileAt(int, int);
  void moveDownHeavyBlock();

  bool isHintSet();
  int getScore();
  BlockType getNextBlockType();
  int getLevel();
  bool getIsGameOver();

  friend std::ostream &operator<<(std::ostream &, Board &);

private:
  void initGrid();
  void initBlockSelector();
  void initBlocks();
  void deleteGrid();
  void checkForFullRow();
  void clearRow(int);
  void moveRowsDownOneRow(int);
  int getPointsFromClearedRows(int);
  int getPointsFromClearedBlock(Block *);
  void updateScore(int);
  bool doesLevelDropTiles();
  void dropTileBlock();
  void setupNextBlocks();
  void drawHint();
  PImpl_B *board_;
};

#endif
