#ifndef _BOARD_
#define _BOARD_

#include <iostream>
#include <vector>

#include "quadris.h"
#include "subject.h"
#include "tile.h"

#define MIN_LEVEL 0
#define MAX_LEVEL 4

// Forward declaration of Block class
class Block;

//Forward declaration of BlockType
enum class BlockType: int;

class Board: public Subject{

	  public:
		Board();
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
        std::vector<Tile> board;
};

#endif
