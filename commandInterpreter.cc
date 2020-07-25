#include "commandInterpreter.h"
#include "quadris.h"
#include <string>
#include <vector>

using namespace std;

CommandInterpreter::CommandInterpreter(){
    commandInterpreter_ = new PImpl_CI;
    initCmdActions();
    initCmdStrings();
}

CommandInterpreter::~CommandInterpreter(){}

void CommandInterpreter::initCmdActions(){
    if (nullptr == commandInterpreter_){
        return;
    }

    commandInterpreter_->cmdActions_.clear();

    //TODO: REFACTOR THIS
    commandInterpreter_->cmdActions_["left"] = vector<Action>(LEFT);
    commandInterpreter_->cmdActions_["right"] = vector<Action>(RIGHT);
    commandInterpreter_->cmdActions_["down"] = vector<Action>(DOWN);
    commandInterpreter_->cmdActions_["clockwise"] = vector<Action>(CLOCKWISE);
    commandInterpreter_->cmdActions_["counterclockwise"] = vector<Action>(COUNTERCLOCKWISE);
    commandInterpreter_->cmdActions_["drop"] = vector<Action>(DROP);
    commandInterpreter_->cmdActions_["levelup"] = vector<Action>(LEVELUP);
    commandInterpreter_->cmdActions_["leveldown"] = vector<Action>(LEVELDOWN);
    commandInterpreter_->cmdActions_["norandom"] = vector<Action>(NORANDOM);
    commandInterpreter_->cmdActions_["random"] = vector<Action>(RANDOM);
    commandInterpreter_->cmdActions_["sequence"] = vector<Action>(SEQUENCE);
    commandInterpreter_->cmdActions_["i"] = vector<Action>(I);
    commandInterpreter_->cmdActions_["j"] = vector<Action>(J);
    commandInterpreter_->cmdActions_["l"] = vector<Action>(L);
    commandInterpreter_->cmdActions_["s"] = vector<Action>(S);
    commandInterpreter_->cmdActions_["z"] = vector<Action>(Z);
    commandInterpreter_->cmdActions_["o"] = vector<Action>(O);
    commandInterpreter_->cmdActions_["t"] = vector<Action>(T);
    commandInterpreter_->cmdActions_["restart"] = vector<Action>(RESTART);
    commandInterpreter_->cmdActions_["hint"] = vector<Action>(HINT);
}

void CommandInterpreter::initCmdStrings(){
    if (nullptr == commandInterpreter_){
        return;
    }

    commandInterpreter_->cmdStrings_.clear();

    //TODO: Refactor
    commandInterpreter_->cmdStrings_["lef"] = "left";
    commandInterpreter_->cmdStrings_["ri"] = "right";
    commandInterpreter_->cmdStrings_["do"] = "down";
    commandInterpreter_->cmdStrings_["cl"] = "clockwise";
    commandInterpreter_->cmdStrings_["co"] = "counterclockwise";
    commandInterpreter_->cmdStrings_["dr"] = "drop";
    commandInterpreter_->cmdStrings_["levelu"] = "levelup";
    commandInterpreter_->cmdStrings_["leveld"] = "leveldown";
    commandInterpreter_->cmdStrings_["n"] = "norandom";
    commandInterpreter_->cmdStrings_["ra"] = "random";
    commandInterpreter_->cmdStrings_["se"] = "sequence";
    commandInterpreter_->cmdStrings_["i"] = "i";
    commandInterpreter_->cmdStrings_["j"] = "j";
    commandInterpreter_->cmdStrings_["l"] = "l";
    commandInterpreter_->cmdStrings_["s"] = "s";
    commandInterpreter_->cmdStrings_["z"] = "z";
    commandInterpreter_->cmdStrings_["o"] = "o";
    commandInterpreter_->cmdStrings_["t"] = "t";
    commandInterpreter_->cmdStrings_["re"] = "restart";
    commandInterpreter_->cmdStrings_["h"] = "hint";
}

void CommandInterpreter::handleCommand(string command){
    vector<Action> actions = getCommandAction(command);
    for (int i = 0; i < actions.size(); i++){
        if (actions[i] != BAD_COMMAND){
            executeCommand(actions[i]);
        }
    }
}

vector<Action> CommandInterpreter::getCommandAction(string command){
    if (commandInterpreter_->cmdActions_.count(command)>0){
        return commandInterpreter_->cmdActions_[command];
    }
    else{
        //check if a minimal string is contained in command
        for (auto const& it : commandInterpreter_->cmdStrings_)
        {
            if (it.first == command.substr(0, it.first.length())){
                return commandInterpreter_->cmdActions_[it.second];
            }
        }
    }
    return vector<Action>(BAD_COMMAND);
}

void executeCommand(Action action){
    switch(action){
        case LEFT:
            break;
        case RIGHT:
            break;
        case DOWN:
            break;
        case CLOCKWISE:
            break;
        case COUNTERCLOCKWISE:
            break;
        case DROP:
            break;
        case LEVELUP:
            break;
        case LEVELDOWN:
            break;
        case NORANDOM:
            break;
        case RANDOM:
            break;
        case SEQUENCE:
            break;
        case I:
            break;
        case J:
            break;
        case L:
            break;
        case S:
            break;
        case Z:
            break;
        case O:
            break;
        case T:
            break;
        case RESTART:
            break;
        case HINT:
            break;
    }
}