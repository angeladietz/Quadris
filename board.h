#ifndef _BOARD_
#define _BOARD_

#include <iostream>
#include <vector>
#include <string>
#include "quadris.h"
#include "subject.h"
#include "tile.h"
#include "block.h"
#include "blockSelectionStrategy.h"

#define MIN_LEVEL 0
#define MAX_LEVEL 4
#define BOARD_WIDTH 11
#define BOARD_HEIGHT 18

struct PImpl_B{
    Block* curBlock_;
    Block* nextBlock_;
    std::vector<std::vector<Tile*> > grid_;
    int curLevel_;
    BlockSelectionStrategy* blockSelectionStrategy_;
    std::string scriptFile_;
    int curScore_;
    int highScore_;
};

// Forward declaration of Block class
class Block;

//Forward declaration of BlockType
enum class BlockType: int;

class Board: public Subject{
	public:
		Board(int, std::string);
        ~Board();
		
        Tile* getTileAt_(int, int);
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
        void reset();
        void updateTileAt(int, int);

        friend std::ostream& operator<<(std::ostream&, Board&);

    private:
        void initGrid();
        void initBlockSelector();
        void deleteGrid();
        PImpl_B* board_;
};

#endif
