#ifndef _QUADRIS_
#define _QUADRIS_

#include "board.h"
#include "blockSelectionStrategy.h"

struct PImpl_Q{
	Board* board_;
	BlockSelectionStrategy* blockSelectionStrategy_;
	int level_;
	int score_;
};

class Quadris{
	public:
		Quadris();
		~Quadris();
		void startGame();
		int getScore() const;
		void updateScore(int);
		void restartGame();
		void changeLevel(int);

	private:
		PImpl_Q* quadris_;
};

#endif
