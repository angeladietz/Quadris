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
}

void TextDisplay::read() {
  string cmd = "";
  if (cin >> cmd) {
    cerr << "cmd is " << cmd << endl;
    //controller_->handleCommand(cmd); 
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  out << "Level:	    " << td.level_ << endl;
  out << "Score:	    " << td.currScore_ << endl;
  out << "High Score: " << td.highScore_ << endl;
  out << td.board_;
  return out;
}
