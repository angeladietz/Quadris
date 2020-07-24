#ifndef _QUADRIS_
#define _QUADRIS_

#include "board.h"

class Quadris{
	public:
		Quadris();
		~Quadris();
		void startGame();
		int getScore() const;
		void updateScore(int);
		void restartGame();
		void changeLevel(int);
};

#endif
