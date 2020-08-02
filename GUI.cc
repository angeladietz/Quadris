#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <gdkmm/pixbuf.h>
#include "board.h"
#include "Block.h"
#include "controller.h"
#include "observer.h"
#include "GUI.h"

using std::string;
using std::vector;
using std::to_string;

const char * image_names[] = {   
	// Set up block images
	 "empty.png", "I_Block.jpg","O_Block.jpg","Z_Block.jpg","S_Block.jpg","J_Block.jpg","L_Block.jpg","T_Block.jpg","Star_Block.jpg","Hint_Block.jpg"
	
}; 

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file(name);
} // createPixbuf

//Constructor
GUI::GUI(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder, controller* controller, board* board): Gtk::Window(cobject), _builder(builder){
	controller_ = controller;
	board_ = board;
	//board_->subscribe(this); //our board doesn't have subscribe method
	
	//STL command to fill the blocks vector with the Pixbuf objects based on the image names in image_names
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
			   std::back_inserter(this->blocks), &createPixbuf );
	
	//Retrieve all widgets.
	_builder->get_widget("objectContainer", objectContainer);
	_builder->get_widget("Level", levelLabel);
	_builder->get_widget("Score", scoreLabel);
	_builder->get_widget("highScore", hiScoreLabel);
	_builder->get_widget("gameBoard", gameGrid);
	_builder->get_widget("nextLabel", nextLabel);
	_builder->get_widget("nextGrid", nextGrid);
	_builder->get_widget("controlSeparator", controlSeparator);
	
	//Iterate through all the image widgets for the game board and store them in the gameBlocks array
	string tempImageName = "image";
	string imageNo = "";
	Gtk::Image *tempImage;
	int currImage = 0;
	for(int i = 0; i < 18; i++){
		for(int j = 0; j < 11; j++){
			imageNo = std::to_string(currImage);
			tempImageName = "image" + imageNo;
			_builder->get_widget(tempImageName, tempImage);
			gameBlocks.at(i).at(j) = tempImage;
			currImage++;
		}
	}
	
	//Iterate through all the image widgets for the next display and store them in the gameBlocks array
	tempImageName = "nextBlock";
	imageNo = "";
	currImage = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 4; j++){
			imageNo = std::to_string(currImage);
			tempImageName = "nextBlock" + imageNo;
			_builder->get_widget(tempImageName, tempImage);
			nextBlock.at(i).at(j) = tempImage;
			currImage++;
		}
	}

	_builder->get_widget("startButton", startButton);
	
	//Set all images in the gameboard to an empty png
	for (int i = 0; i < NUMBER_ROWS; i++) {
		for (int k = 0; k < NUMBER_COLUMNS; k++) {
			((this->gameBlocks).at(i).at(k))->set(this->blocks.at(0));
		}
	}
	
	this -> clearNextDisplay();
	// Associate button "clicked" events with local onButtonClicked() method defined below.
	startButton->signal_clicked().connect( sigc::mem_fun( *this, &GraphicalDisplay::startButtonClicked ) );
	
}

//Destructor
GraphicalDisplay::~GraphicalDisplay(){
    
    if (mainContainer != nullptr){
        delete mainContainer;
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

void GraphicalDisplay::draw(){	
	std::vector<std::vector<char>> tileBoard = board_->getBoard();
	
	for (int i = 0; i < NUMBER_ROWS; i++) {
		for (int k = 0; k < NUMBER_COLUMNS; k++) {
			
			switch(tileBoard.at(k).at(i)){
			case 'I':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(1));
				break;
			case 'O':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(2));
				break;
			case 'Z':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(3));
				break;
			case 'S':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(4));
				break;
			case 'J':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(5));
				break;
			case 'L':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(6));
				break;
			case 'T':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(7));
				break;
			case '*':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(8));
				break;
			case '?':
				((this->gameBlocks).at(i).at(k))->clear();
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(9));
				break;
			default:
				((this->gameBlocks).at(i).at(k))->set(this->blocks.at(0));
			}
		}
	}
	
	this->clearNextDisplay();
	
	switch (board_->getNextBlockType()) {
		case I_BLOCK:
			for(int k = 0; k < 4; k++){ 
				((this->nextBlock).at(1).at(k))->set(this->blocks.at(1));
			}
			break;
		case O_BLOCK:
			for(int i = 1; i < 3; i++){
				for(int k = 0; k < 2; k++){ 
					((this->nextBlock).at(i).at(k))->set(this->blocks.at(2));
				}
			}
			break;
		case Z_BLOCK:
			for(int k = 0; k < 2; k++){ 
				((this->nextBlock).at(1).at(k))->set(this->blocks.at(3));
			}
			for(int k = 1; k < 3; k++){ 
				((this->nextBlock).at(2).at(k))->set(this->blocks.at(3));
			}
			break;
		case S_BLOCK:
			for(int k = 2; k < 4; k++){ 
				((this->nextBlock).at(1).at(k))->set(this->blocks.at(4));
			}
			for(int k = 1; k < 3; k++){ 
				((this->nextBlock).at(2).at(k))->set(this->blocks.at(4));
			}
			break;
		case J_BLOCK:
			((this->nextBlock).at(1).at(0))->set(this->blocks.at(5));
			for(int k = 0; k < 3; k++){ 
				((this->nextBlock).at(2).at(k))->set(this->blocks.at(5));
			}
			break;
		case L_BLOCK:
			((this->nextBlock).at(1).at(3))->set(this->blocks.at(6));
			for(int k = 1; k < 4; k++){ 
				((this->nextBlock).at(2).at(k))->set(this->blocks.at(6));
			}
			break;
		case T_BLOCK:
			for(int k = 0; k < 3; k++){ 
				((this->nextBlock).at(1).at(k))->set(this->blocks.at(7));
			}
			((this->nextBlock).at(2).at(1))->set(this->blocks.at(7));
			break;
	}
	
 
    levelLabel->set_text("Level: " + to_string(board_->getCurrentLevel()));
    scoreLabel->set_text("Score: " + to_string(board_->getCurrentScore()));
    highScoreLabel->set_text("Hi Score: " + to_string(board_->getHighScore()));
    
    while(Gtk::Main::events_pending()) Gtk::Main::iteration();
}

void GraphicalDisplay::startButtonClicked() {
	this->startButton->hide();
	play();
	this->hide();
}

void GraphicalDisplay::clearNextDisplay(){
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 4; k++) {
			((this->nextBlock).at(i).at(k))->set(this->blocks.at(0));
		}
	}
}

