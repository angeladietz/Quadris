#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <string>
#include <vector>
#include "quadris.h"
#include "commandInterpreter.h"

struct PImpl_C{
    CommandInterpreter* commandInterpreter_;
	Board* board_;
};

class Controller {
	public:
		Controller(Board*);
        ~Controller();
		void handleCommand(std::string);
    
    private:
        std::vector<std::string> ParseCommand(std::string);
		std::string ConvertToLowercase(std::string);
		std::vector<std::string> SplitCommand(std::string);
        void executeCommand(Action, std::string);
        void HandleCommandSequenceFromFile(std::string);
        bool DoesRequireFile(Action);
        PImpl_C* controller_;
};

#endif
