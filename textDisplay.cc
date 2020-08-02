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
  highScore = board_->getHighScore();
  level = board_->getLevel();
  print();
}

void TextDisplay::poll() {

    string command;
    while (cin >> command) {
        controller_->handleCommand(command);
    }

}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  out << "Level:	    " << td.level << endl;
  out << "Score:	    " << td.currScore << endl;
  out << "High Score: " << td.highScore << endl;
  out << td.board_;
  return out;
}

void TextDisplay::print() {
    std::cout << "Level:	    " << level << endl;
    std::cout << "Score:	    " << currScore << endl;
    std::cout << "High Score: " << highScore << endl;
    std::cout << *board_;
}
