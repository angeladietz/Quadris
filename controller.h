#ifndef _CONTROLLER_
#define _CONTROLLER_

#include "board.h"
#include "commandInterpreter.h"
#include <string>
#include <vector>

struct PImpl_C {
  CommandInterpreter *commandInterpreter_;
  Board *board_;
};

class Controller {
public:
  Controller(Board *);
  ~Controller();
  void handleCommand(std::string);

private:
  std::string ConvertToLowercase(std::string);
  std::vector<std::string> SplitCommand(std::string);
  void executeCommand(Action, std::string = "");
  void HandleCommandSequenceFromFile(std::string);
  bool DoesRequireFile(Action);
  void finishCommandExecution();
  PImpl_C *controller_;
};

#endif
