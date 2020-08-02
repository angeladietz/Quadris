#include "commandInterpreter.h"
#include "quadris.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

CommandInterpreter::CommandInterpreter(){
    commandInterpreter_ = new PImpl_CI;
    initCmdActions();
    initCmdStrings();
}

CommandInterpreter::~CommandInterpreter(){
    delete commandInterpreter_;
}

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

vector<Action> CommandInterpreter::getCommands(string command){
    int multiplier = getMultiplier(command);

    if (multiplier == -1){
        return vector<Action>(BAD_COMMAND);
    }

    string cmdText = getCommandText(command, multiplier);

    vector<Action> actions;
    vector<Action> multipliedActions;

    if (commandInterpreter_->cmdActions_.count(cmdText) > 0){
        actions = commandInterpreter_->cmdActions_[cmdText];
    }
    else{
        //check if a minimal string is a prefix of command
        for (auto const& it : commandInterpreter_->cmdStrings_)
        {
            if (it.first == cmdText.substr(0, it.first.length())){
                actions = commandInterpreter_->cmdActions_[it.second];
            }
        }
    }

    if (actions.size() > 0){
        for (int i = 0; i < multiplier; i++){
            for (int j = 0; j < actions.size(); j++){
                multipliedActions.push_back(actions[j]);
            }
        }
        return multipliedActions;
    }

    return vector<Action>(BAD_COMMAND);
}

int CommandInterpreter::getMultiplier(string command){
    string multStr = "";
    int multInt = -1;
    bool hasMultiplier = false;

    for (int i = 0; i < command.size(); i++){
        if (isdigit(command[i])){
            hasMultiplier = true;
            multStr += command[i];
        }
        else{
            break;
        }
    }

    if (!hasMultiplier){
        return 1;
    }

    multInt = stoi(multStr);

    if (multInt > 0){
        return multInt;
    }

    return -1;
}

string CommandInterpreter::getCommandText(string command, int multiplier){
    string mult = to_string(multiplier);
    if (mult == "1" && command[0] != '1') {
        return command;
    }
    string cmdText = command.substr(mult.size());
    return cmdText;
}
