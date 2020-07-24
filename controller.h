#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <string>
#include "quadris.h"
#include "commandInterpreter.h"

class Controller {
	public:
		Controller();
        ~Controller();
		void handleCommand(std::string);
    
    private:
        CommandInterpreter commandIneterpreter_;
};

#endif
