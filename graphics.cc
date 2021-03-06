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
#include "graphics.h"
#include "quadris.h"

using namespace std;

//constructor
Graphics::Graphics(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder, Controller* controller, Board* board, Quadris* quadris): Gtk::Window(cobject), _builder(builder) {

	controller_ = controller;
	board_ = board;
	quadris_ = quadris;

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

	levelLabel->set_text("Level: 0");
    scoreLabel->set_text("Score: 0");
    hiScoreLabel->set_text("Hi Score: " + to_string(highScore));
	
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
	
	clearNextBlock();
	startButton->signal_clicked().connect( sigc::mem_fun( *this, &Graphics::startButtonClicked ) );
}

//Destructor
Graphics::~Graphics(){
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

//draw blocks on the gui
void Graphics::update(){

	levelLabel->set_text("Level: " + to_string(board_->getLevel()));
    scoreLabel->set_text("Score: " + to_string(board_->getScore()));
    hiScoreLabel->set_text("Hi Score: " + to_string(highScore));

	char tile;
	//iterate over text display board to update gui
	for (int row = 0; row < BOARD_HEIGHT; row++){
        for (int col = 0; col < BOARD_WIDTH; col++) {
			tile = board_->getTileAt(col,row)->getTileValue();
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
				case '?':
					drawBlocks[row][col]->SetBlock(CDrawingArea::HINTBLOCK);
					break;
				case ' ':
					drawBlocks[row][col]->SetBlock(CDrawingArea::EMPTYBLOCK);
					break;
			}
        }
    }

	clearNextBlock();
	BlockType next = board_->getNextBlockType();

	//add next block to gui
	switch (next) {
		case 0: //IBlock
			for(int j = 0; j < PREVIEW_SIZE; j++){ 
				nextBlock[2][j]->SetBlock(CDrawingArea::IBLOCK);
			}
			break;
		case 1: //JBlock
			nextBlock[1][0]->SetBlock(CDrawingArea::JBLOCK);
			for(int j = 0; j < PREVIEW_SIZE-1; j++){ 
				nextBlock[2][j]->SetBlock(CDrawingArea::JBLOCK);
			}
			break;
		case 2: //LBlock
			nextBlock[1][3]->SetBlock(CDrawingArea::LBLOCK);
			for(int j = 1; j < PREVIEW_SIZE; j++){ 
				nextBlock[2][j]->SetBlock(CDrawingArea::LBLOCK);
			}
			break;
		case 3: //SBlock
			for(int j = 1; j < PREVIEW_SIZE-1; j++){ 
				nextBlock[1][j]->SetBlock(CDrawingArea::SBLOCK);
			}
			for(int j = 0; j < PREVIEW_SIZE-2; j++){ 
				nextBlock[2][j]->SetBlock(CDrawingArea::SBLOCK);
			}
			break;
		case 4: //ZBlock
			for(int j = 0; j < PREVIEW_SIZE-2; j++){ 
				nextBlock[1][j]->SetBlock(CDrawingArea::ZBLOCK);
			}
			for(int j = 1; j < PREVIEW_SIZE-1; j++){ 
				nextBlock[2][j]->SetBlock(CDrawingArea::ZBLOCK);
			}
			break;
		case 5: //OBlock
			for(int i = 1; i < PREVIEW_SIZE-1; i++){
				for(int j = 0; j < PREVIEW_SIZE-2; j++){ 
					nextBlock[i][j]->SetBlock(CDrawingArea::OBLOCK);
				}
			}
			break;
		case 6: //TBlock
			for(int j = 0; j < PREVIEW_SIZE-1; j++){ 
				nextBlock[1][j]->SetBlock(CDrawingArea::TBLOCK);
			}
			nextBlock[2][1]->SetBlock(CDrawingArea::TBLOCK);
			break;
		default:
			break;
	}

	while(Gtk::Main::events_pending()) Gtk::Main::iteration();
}

//quit
void Graphics::OnQuit(){
	hide(); 
}

//Hide start button and start game when start button is clicked
void Graphics::startButtonClicked(){
	this->startButton->hide();
	char* quadris[0];
	quadris_->start();
}

//Clear next block
void Graphics::clearNextBlock(){
	for (int i = 0; i < PREVIEW_SIZE; i++) {
		for (int j = 0; j < PREVIEW_SIZE; j++) {
			nextBlock[i][j]->SetBlock(CDrawingArea::EMPTYBLOCK);
		}
	}
}
