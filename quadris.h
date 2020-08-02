#ifndef _QUADRIS_
#define _QUADRIS_

#include "controller.h"
#include "observer.h"
#include <string>

//Forward declaration of Board class
class Board;

struct PImpl_Q{
	Board* board_;
	Controller* controller_;
	std::vector<Observer*> views_;
	bool textOnly_;
	int level_;
	std::string scriptFile_;
	int highScore_;
};

class Quadris {
	public:
		Quadris(bool, int, std::string);
		~Quadris();
		void playGame();
		int getScore() const;
		void updateScore(int);
		void restartGame();

	private:
		void resetQuadrisParams();
		PImpl_Q* quadris_;
};

#endif
