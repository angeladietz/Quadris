#include "controller.h"
#include "commandInterpreter.h"
#include "quadris.h"
#include "block.h"
#include <cstddef>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

Controller::Controller(Board* b){
    controller_ = new PImpl_C;
    controller_->commandInterpreter_ = new CommandInterpreter();
    controller_->board_ = b;
}

Controller::~Controller(){
    if (nullptr != controller_){
        if (nullptr != controller_->commandInterpreter_){
            delete controller_->commandInterpreter_;
        }
        delete controller_;
    }
}

vector<string> Controller::ParseCommand(string command){
    return SplitCommand(command);
}

vector<string> Controller::SplitCommand(string command){
    istringstream iss(command);
    vector<string> cmds{istream_iterator<string>{iss}, istream_iterator<string>{}};
    return cmds;
}

string Controller::ConvertToLowercase(string command){
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    return command;
}

bool Controller::DoesRequireFile(Action action){
    if (action == SEQUENCE || action == NORANDOM){
        return true;
    }
    return false;
}

void Controller::handleCommand(string command){
    vector<string> cmds = ParseCommand(command);
    vector<Action> actions;
    for (size_t i = 0; i < cmds.size(); i++){
	    actions = controller_->commandInterpreter_->getCommands(ConvertToLowercase(cmds[i]));

        for (size_t j = 0; j < actions.size(); j++){
			if (controller_->board_->getIsGameOver()){
				return;
			}
            if (DoesRequireFile(actions[j])){
                if (i < cmds.size()-1){
                    executeCommand(actions[j], cmds[++i]);
                }
            }
            else if (actions[j] != BAD_COMMAND){
                executeCommand(actions[j]);
            }
        }
		if (!controller_->board_->getIsGameOver()){
			finishCommandExecution();
		}
    }
}

void Controller::HandleCommandSequenceFromFile(string filename){
    ifstream seqFile;

    //TODO: ADD EXCEPTION HANDLING!
    seqFile.open(filename);

    if (seqFile.is_open()){
        string command = "";
        string nextCmd;
        while(seqFile>>nextCmd){

            command += nextCmd + " ";
        }
        seqFile.close();

        handleCommand(command);
    }
}

void Controller::executeCommand(Action action, string filename){

    if (controller_->board_->isHintSet()) {
        controller_->board_->clearHint();
    }

    switch(action){
        case LEFT:
            controller_->board_->moveCurBlockLeft();
            break;
        case RIGHT:
            controller_->board_->moveCurBlockRight();
            break;
        case DOWN:
            controller_->board_->moveCurBlockDown();
            break;
        case CLOCKWISE:
            controller_->board_->rotateCurBlockClockwise();
            break;
        case COUNTERCLOCKWISE:
            controller_->board_->rotateCurBlockCounterClockwise();
            break;
        case DROP:
            controller_->board_->dropCurBlock();
            break;
        case LEVELUP:
            controller_->board_->levelUp();
            break;
        case LEVELDOWN:
            controller_->board_->levelDown();
            break;
        case NORANDOM:
            controller_->board_->setNoRand(filename);
            break;
        case SEQUENCE:
            HandleCommandSequenceFromFile(filename);
            break;
        case RANDOM:
            controller_->board_->setRand();
            break;
        case I:
            controller_->board_->setCurBlock(IBlock);
            break;
        case J:
            controller_->board_->setCurBlock(JBlock);
            break;
        case L:
            controller_->board_->setCurBlock(LBlock);
            break;
        case S:
            controller_->board_->setCurBlock(SBlock);
            break;
        case Z:
            controller_->board_->setCurBlock(ZBlock);
            break;
        case O:
            controller_->board_->setCurBlock(OBlock);
            break;
        case T:
            controller_->board_->setCurBlock(TBlock);
            break;
        case RESTART:
            controller_->board_->restart();
            break;
        case HINT:
            controller_->board_->showHint();
            break;
    }
}

// Executes actions necessary after each command
void Controller::finishCommandExecution(){
    controller_->board_->moveDownHeavyBlock();
    controller_->board_->notifyObservers();
}
