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

	for(int i = 0; i < BOARD_HEIGHT; i++) {
		for(int j = 0; j < BOARD_WIDTH; j++) {
			_builder->get_widget_derived("drawingArea"+to_string(num1++), temp);
			drawBlocks[i][j] = temp;
		}
	}

	//build nextBlock vector
	CDrawingArea *temp2;
	int num2 = 0;

	for(int i = 0; i < PREVIEW_SIZE; i++) {
		for(int j = 0; j < PREVIEW_SIZE; j++) {
			_builder->get_widget_derived("nextBlockArea"+to_string(num2++), temp2);
			nextBlock[i][j] = temp2;
		}
	}
	
	//fill drawBlocks with empty blocks
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			drawBlocks[i][j]->SetBlock(CDrawingArea::EMPTYBLOCK);
		}
	}
	
	//clear next block
	for (int i = 0; i < PREVIEW_SIZE; i++) {
		for (int j = 0; j < PREVIEW_SIZE; j++) {
			nextBlock[i][j]->SetBlock(CDrawingArea::EMPTYBLOCK);
		}
	}

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	startButton->signal_clicked().connect( sigc::mem_fun( *this, &GUI::startButtonClicked ) );
	
}

//Destructor
//TODO: FIX THIS
GUI::~GUI(){
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

    if (objectContainer != nullptr){
        delete objectContainer;
    }
    if (scoreBoard != nullptr){
        delete scoreBoard;
    }
    if (controlBox != nullptr){
        delete controlBox;
    }
    if (gameGrid != nullptr){
        delete gameGrid;
    }
    if (levelLabel != nullptr){
        delete levelLabel;
    }
    if (scoreLabel != nullptr){
        delete scoreLabel;
    }
    if (hiScoreLabel != nullptr){
        delete hiScoreLabel;
    }
    if (startButton != nullptr){
        delete startButton;
    }
    if (nextLabel != nullptr){
        delete nextLabel;
    }
    if (nextGrid != nullptr){
        delete nextGrid;
    }
	
	if (controlSeparator != nullptr){
        delete controlSeparator;
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
    
    for (int i = 0; i < drawBlocks.size(); i++){
        for (int j = 0; j < drawBlocks.at(i).size(); j++){
            if (drawBlocks.at(i).at(j) != nullptr){
                delete drawBlocks.at(i).at(j);
            }
        }
    }
}

void GUI::draw(){
	//iterate over text display board
	for (int row = 0; row < BOARD_HEIGHT; row++){
	    row+1;
        for (auto col: board_->grid_[row]) {
            board_[row][col] 
        }
        out << std::endl;
    }
}