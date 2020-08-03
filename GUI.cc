#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <gtkmm.h>
#include "board.h"
#include "block.h"
#include "controller.h"
#include "observer.h"
#include "GUI.h"
#include "quadris.h"

using namespace std;

//constructor
GUI::GUI(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder, Controller* controller, Board* board): Gtk::Window(cobject), _builder(builder) {

	controller_ = controller;
	board_ = board;

	_builder->get_widget("objectContainer", objectContainer);
	_builder->get_widget("scoreBoard", scoreBoard);
	_builder->get_widget("controlBox", controlBox);
	_builder->get_widget("levelLabel", levelLabel);
	_builder->get_widget("scoreLabel", scoreLabel);
	_builder->get_widget("hiScoreLabel", hiScoreLabel);
	_builder->get_widget("gameBoard", gameBoard);
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
GUI::~GUI(){
    if (objectContainer != nullptr){
        delete objectContainer;
    }
    if (scoreBoard != nullptr){
        delete scoreBoard;
    }
    if (controlBox != nullptr){
        delete controlBox;
    }
    if (gameBoard != nullptr){
        delete gameBoard;
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
	
	for (int i = 0; i < nextBlock.size(); i++){
        for (int j = 0; j < nextBlock[i].size(); j++){
            if (nextBlock[i][j] != nullptr){
                delete nextBlock[i][j];
            }
        }
    }
    
    for (int i = 0; i < drawBlocks.size(); i++){
        for (int j = 0; j < drawBlocks[i].size(); j++){
            if (drawBlocks[i][j] != nullptr){
                delete drawBlocks[i][j];
            }
        }
    }
}

//draw blocks
void GUI::update(){
	char tile;
	//iterate over text display board
	for (int row = 0; row < BOARD_HEIGHT; row++){
        for (int col = 0; col < BOARD_WIDTH; col++) {
			tile = board_->getTileAt(row,col)->getTileValue();
			switch(tile){
				case 'I':
					drawBlocks[row][col]->SetBlock(CDrawingArea::IBLOCK);
					break;
				case 'J':
					drawBlocks[row][col]->SetBlock(CDrawingArea::JBLOCK);
					break;
				case 'L':
					drawBlocks[row][col]->SetBlock(CDrawingArea::LBLOCK);
					break;
				case 'O':
					drawBlocks[row][col]->SetBlock(CDrawingArea::OBLOCK);
					break;
				case 'S':
					drawBlocks[row][col]->SetBlock(CDrawingArea::SBLOCK);
					break;
				case 'Z':
					drawBlocks[row][col]->SetBlock(CDrawingArea::ZBLOCK);
					break;
				case 'T':
					drawBlocks[row][col]->SetBlock(CDrawingArea::TBLOCK);
					break;
				case '*':
					drawBlocks[row][col]->SetBlock(CDrawingArea::STARBLOCK);
					break;
				case ' ':
					drawBlocks[row][col]->SetBlock(CDrawingArea::EMPTYBLOCK);
					break;
			}
        }
    }
}

//quit
void GUI::OnQuit(){
	hide(); 
}

//OnClick handler for start button
void GUI::startButtonClicked(){
	this->startButton->hide();
	char* quadris[0];
    quadris_->playGame(1, quadris);
	this->hide();
}
