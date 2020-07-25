#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <string>
#include "quadris.h"
#include "commandInterpreter.h"

class Controller {
	public:
		Controller(Quadris*);
        ~Controller();
		void handleCommand(std::string);
    
    private:
        CommandInterpreter* commandInterpreter_;
};

#endif
