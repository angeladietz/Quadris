#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <string>
#include "quadris.h"

class Controller {
	public:
		Controller();
        ~Controller();
		void handleCommand(string);
    
    private:
        CommandInterpreter commandIneterpreter_;
};

#endif
