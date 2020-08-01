#ifndef _COMMANDINTERPRETER_
#define _COMMANDINTERPRETER_

#include <string>
#include <map>
#include <vector>

enum Action { LEFT, RIGHT, DOWN, CLOCKWISE, COUNTERCLOCKWISE, DROP,
			  LEVELUP, LEVELDOWN, NORANDOM, RANDOM, SEQUENCE,
			  I,J,L,S,Z,O,T, RESTART, HINT, BAD_COMMAND};

struct PImpl_CI{
	std::map<std::string, std::vector<Action> > cmdActions_;
	std::map<std::string, std::string> cmdStrings_;
};

class CommandInterpreter {
	public:
		CommandInterpreter();
        ~CommandInterpreter();
		std::vector<Action> getCommands(std::string);
	
	private:
		void initCmdActions();
		void initCmdStrings();
		int getMultiplier(std::string);
		std::string getCommandText(std::string, int);

		PImpl_CI* commandInterpreter_;
};

#endif
