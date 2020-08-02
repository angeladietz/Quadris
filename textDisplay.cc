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
  nextBlock_ = board_->getNextBlock();
  currScore_ = board_->getScore();
  highScore_ = highScore;
  level_ = board_->getLevel();
  print();
  poll();
}

void TextDisplay::poll() {

   cout << ">";
   string command;
   if (cin >> command){
	   controller_->handleCommand(command);
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
}
