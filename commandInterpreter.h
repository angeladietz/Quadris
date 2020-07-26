#ifndef _COMMANDINTERPRETER_
#define _COMMANDINTERPRETER_

#include <string>
#include <map>
#include <vector>
#include "controller.h"
#include "quadris.h"

enum Action {LEFT, RIGHT, DOWN, CLOCKWISE, COUNTERCLOCKWISE, DROP,
			  LEVELUP, LEVELDOWN, NORANDOM, RANDOM, SEQUENCE,
			  I,J,L,S,Z,O,T, RESTART, HINT, BAD_COMMAND};

struct PImpl_CI{
	std::map<std::string, std::vector<Action> > cmdActions_;
	std::map<std::string, std::string> cmdStrings_;
	Quadris* quadris_;
};

class CommandInterpreter {
	public:
		CommandInterpreter(Quadris*);
        ~CommandInterpreter();
		void handleCommand(std::string);
	
	private:
		void initCmdActions();
		void initCmdStrings();
		vector<Action> getCommandAction(string);
		void executeCommand(Action);

		PImpl_CI* commandInterpreter_;
};

#endif
