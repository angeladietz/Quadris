#ifndef _QUADRIS_
#define _QUADRIS_

#include "board.h"
#include "controller.h"
#include <string>

struct PImpl_Q{
	Board* board_;
	Controller* controller_;
	std::vector<Observer*> views_;
	bool textOnly_;
	int level_;
	std::string scriptFile_;
	int highScore_;
};

class Quadris{
	public:
		Quadris(bool, int, std::string);
		~Quadris();
		void playGame();
		int getScore() const;
		void updateScore(int);
		void restartGame();

	private:
		PImpl_Q* quadris_;
};

#endif
