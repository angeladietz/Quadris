#ifndef _BOARD_
#define _BOARD_

#include <iostream>
#include "quadris.h"
#include "subject.h"

class Board: public Subject{
	public:
		Board();
        ~Board();
		
        void moveCurBlockLeft();
        void moveCurBlockRight();
        void moveCurBlockDown();
        void rotateCurBlockCounterClockwise();
        void rotateCurBlockClockwise();
        void dropCurBlock();
        void showHint();
        Tile operator[](int);
        void reset();

        friend ostream& operator<<(ostream&, Board&);     
};

#endif
