#ifndef _COMMANDINTERPRETER_
#define _COMMANDINTERPRETER_

#include <string>
#include "controller.h"
#include "quadris.h"

class CommandInterpreter {
	public:
		CommandInterpreter();
        ~CommandInterpreter();
		void executeCommand();
};

#endif
