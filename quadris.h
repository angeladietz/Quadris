#ifndef _QUADRIS_
#define _QUADRIS_

#include "controller.h"
#include "observer.h"
#include "textDisplay.h"
#include "GUI.h"
#include <string>

extern int highScore;

//Forward declaration of Board class
class Board;

struct PImpl_Q{
	Board* board_;
	Controller* controller_;
	GUI* gui_;
	std::vector<Observer*> views_;
	bool textOnly_;
	int level_;
	std::string scriptFile_;
};

class Quadris {
	public:
		Quadris(bool textOnly, int startLevel, std::string scriptFile);
		~Quadris();
		void playGame(int argc, char* argv[]);
		int getScore() const;
		void updateScore(int);
		void restartGame();
		void start();
		void endGame();

	private:
		void resetQuadrisParams();
		PImpl_Q* quadris_;
		TextDisplay* td;
};

#endif
