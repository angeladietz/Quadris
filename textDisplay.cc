#include "textDisplay.h"
#include "controller.h"

using namespace std;

#include <iostream>
#include <vector>

#include "board.h"

TextDisplay::TextDisplay(Board* board, Controller * controller) {

    board_ = board;
    controller_ = controller;

}

TextDisplay::~TextDisplay() {}

void TextDisplay::update() {
  nextBlock = board_->getNextBlock();
  currScore = board_->getScore();
  highScore = highScore_;
  level = board_->getLevel();
}

void TextDisplay::read() {
  string cmd = "";
  if (cin >> cmd) {
    cerr << "cmd is " << cmd << endl;
    //segfaulting here
    //cmd_->getCommands(cmd); 
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  out << "Level:	    " << td.level << endl;
  out << "Score:	    " << td.currScore << endl;
  out << "High Score: " << td.highScore << endl;
  out << td.board_;
  return out;
}
