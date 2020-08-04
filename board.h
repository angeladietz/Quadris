#ifndef _BOARD_
#define _BOARD_

#include <iostream>
#include <vector>
#include <string>
#include "subject.h"
#include "tile.h"
#include "block.h"
#include "blockFactory.h"
#include "blockSelectionStrategy.h"

#define MIN_LEVEL 0
#define MAX_LEVEL 4
#define BOARD_WIDTH 11
#define BOARD_HEIGHT 18

//Forward declaration of Quadris class
class Quadris;

struct PImpl_B{
    Block* curBlock_;
    Block* nextBlock_;
    BlockType nextBlockType_;
    std::vector<std::vector<Tile*> > grid_;
    int curLevel_;
    BlockSelectionStrategy* blockSelectionStrategy_;
    std::string L0SeqFile_;
    std::string noRandFile_;
    int curScore_;
    int highScore_;
    bool isRandom_;
    int blockCount_;
    Quadris* quadris_;
    BlockFactory* blockFactory_;
};

class Board: public Subject {
	public:
		Board(Quadris*, int, std::string);
        ~Board();
		
        Tile* getTileAt(int, int);
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
        Tile operator[](int);
        void restart();
        void updateTileAt(int, int);
        void moveDownHeavyBlock();

        int getScore();
        //int getHighScore();
        BlockType getNextBlockType();
        int getLevel();

        friend std::ostream& operator<<(std::ostream&, Board&);

    private:
        void initGrid();
        void initBlockSelector();
        void initBlocks();
        void deleteGrid();
        void checkForFullRow();
        void clearRow(int);
        void moveRowsDownOneRow(int);
        int  getPointsFromClearedRows(int);
        int  getPointsFromClearedBlock(Block*);
        void updateScore(int);
        bool doesLevelDropTiles();
        void dropTileBlock();
        void setupNextBlocks();
        PImpl_B* board_;
};

#endif
