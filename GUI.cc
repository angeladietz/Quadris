#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <gdkmm/pixbuf.h>
#include "board.h"
#include "block.h"
#include "controller.h"
#include "observer.h"
#include "GUI.h"

using namespace std;

GUI::GUI(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder, Controller* controller, Board* board): Gtk::Window(cobject), _builder(builder){
	controller_ = controller;
	board_ = board;

	_builder->get_widget("objectContainer", objectContainer);
	_builder->get_widget("scoreBoard", scoreBoard);
	_builder->get_widget("controlBox", controlBox);
	_builder->get_widget("levelLabel", levelLabel);
	_builder->get_widget("scoreLabel", scoreLabel);
	_builder->get_widget("hiScoreLabel", hiScoreLabel);
	_builder->get_widget("gameGrid", gameGrid);
	_builder->get_widget("startButton", startButton);
	_builder->get_widget("nextLabel", nextLabel);
	_builder->get_widget("nextGrid", nextGrid);
	_builder->get_widget("controlSeparator", controlSeparator);

	//build drawBlocks vector
	CDrawingArea *temp;
	int num1 = 0;

	for(int i = 0; i < 18; i++) {
		for(int j = 0; j < 11; j++) {
			_builder->get_widget_derived("drawingArea"+to_string(num1++), temp);
			drawBlocks[i][j] = temp;
		}
	}

	//build nextBlock vector
	CDrawingArea *temp2;
	int num2 = 0;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			_builder->get_widget_derived("nextBlockArea"+to_string(num2++), temp2);
			nextBlock[i][j] = temp2;
		}
	}
	
	//fill drawBlocks with empty blocks
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 11; j++) {
			drawBlocks[i][j]->SetBlock(CDrawingArea::EMPTYBLOCK);
		}
	}
	
	//clear next block
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			nextBlock[i][j]->SetBlock(CDrawingArea::EMPTYBLOCK);
		}
	}

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	startButton->signal_clicked().connect( sigc::mem_fun( *this, &GUI::startButtonClicked ) );
	
}

//Destructor
//TODO: FIX THIS
GUI::~GUI(){
    
    if (objectContainer != nullptr){
        delete objectContainer;
    }
    if (labelContainer != nullptr){
        delete labelContainer;
    }
    if (controlContainer != nullptr){
        delete controlContainer;
    }
    if (gameTable != nullptr){
        delete gameTable;
    }
    if (levelLabel != nullptr){
        delete levelLabel;
    }
    if (scoreLabel != nullptr){
        delete scoreLabel;
    }
    if (highScoreLabel != nullptr){
        delete highScoreLabel;
    }
    if (startButton != nullptr){
        delete startButton;
    }
    if (nextBlockLabel != nullptr){
        delete nextBlockLabel;
    }
	
	if (nextBlockContainer != nullptr){
        delete nextBlockContainer;
    }
	
	Gtk::Box *objectContainer;
	Gtk::Box *scoreBoard;
	Gtk::Box *controlBox;
	Gtk::Grid *gameGrid;
	Gtk::Label *levelLabel;
	Gtk::Label *scoreLabel;
	Gtk::Label *hiScoreLabel;
	Gtk::ToggleButton *startButton;
	Gtk::Label *nextLabel;
	Gtk::Grid *nextGrid;
	Gtk::Separator *controlSeparator;
	
	for (int i = 0; i < nextBlock.size(); i++){
        for (int j = 0; j < nextBlock.at(i).size(); j++){
            if (nextBlock.at(i).at(j) != nullptr){
                delete nextBlock.at(i).at(j);
            }
        }
    }
    
    for (int i = 0; i < gameBlocks.size(); i++){
        for (int j = 0; j < gameBlocks.at(i).size(); j++){
            if (gameBlocks.at(i).at(j) != nullptr){
                delete gameBlocks.at(i).at(j);
            }
        }
    }
}

void GUI::draw(){
	//iterate over text display board
	for (int row = 0; row < 18; row++){
	    row+1;
        for (auto col: board_->grid_[row]) {
            board_[row][col] 
        }
        out << std::endl;
    }
}