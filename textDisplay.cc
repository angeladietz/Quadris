#include "textDisplay.h"
#include "controller.h"
#include "quadris.h"

using namespace std;

#include <iostream>
#include <vector>

TextDisplay::TextDisplay(Board* board, Controller * controller) {

    board_ = board;
    controller_ = controller;

}

TextDisplay::~TextDisplay() {}

void TextDisplay::update() {
  nextBlock_ = board_->getNextBlockType();
  currScore_ = board_->getScore();
  highScore_ = highScore;
  level_ = board_->getLevel();
  print();
}

void TextDisplay::poll() {
   string command;
   cout << endl<<">";
   while (getline(cin,command)){
	   controller_->handleCommand(command);
	   cout<<endl<<">";
   }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  out << "Level:	    " << td.level_ << endl;
  out << "Score:	    " << td.currScore_ << endl;
  out << "High Score: " << td.highScore_ << endl;
  out << td.board_;
  return out;
}

void TextDisplay::print() {
    cout << "	Level:	    " << level_ << endl;
    cout << "	Score:	    " << currScore_ << endl;
    cout << "	High Score: " << highScore_ << endl;
    cout << "	-----------"<<endl;
    cout << *board_;
    cout << "	-----------"<<endl;
    cout << "	Next block:"<<endl;
    printBlock(nextBlock_);
}

void TextDisplay::printBlock(BlockType bType){
  switch (bType){
        case IBlock:
            cout << "	IIII"<<endl;
            break;
        case JBlock:
            cout << "	J  "<<endl;
            cout << "	JJJ"<<endl;
            break;
        case LBlock:
            cout << "	  L"<<endl;
            cout << "	LLL"<<endl;
            break;
        case SBlock:
            cout << "	 SS"<<endl;
            cout << "	SS "<<endl;
            break;
        case ZBlock:
            cout << "	ZZ "<<endl;
            cout << "	 ZZ"<<endl;
            break;
        case OBlock:
            cout << "	OO"<<endl;
            cout << "	OO"<<endl;
            break;
        case TBlock:
            cout << "	TTT"<<endl;
            cout << "	 T "<<endl;
            break;
        case TILE_BLOCK:
            cout << "	*"<<endl;
  }
}
