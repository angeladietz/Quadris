#ifndef _QUADRIS_
#define _QUADRIS_

#include "board.h"
#include "blockSelectionStrategy.h"
#include "controller.h"

struct PImpl_Q{
	Board* board_;
	BlockSelectionStrategy* blockSelectionStrategy_;
	Controller* controller_;
	std::vector<Observer*> views_;
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

	private:
		PImpl_Q* quadris_;
};

#endif
