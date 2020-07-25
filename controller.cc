#include "controller.h"
#include "commandInterpreter.h"
#include "quadris.h"
#include <string>

using namespace std;

Controller::Controller(Quadris* q){
    commandInterpreter_ = new CommandInterpreter(q);
}

Controller::~Controller(){
    delete commandInterpreter_;
}

void Controller::handleCommand(string command){
    commandInterpreter_->handleCommand(command);
}

