#include "textDisplay.h"

using namespace std;

#include <iostream>
#include <vector>

#include "board.h"

TextDisplay::TextDisplay() {
  for (int i = 0; i < 15; ++i) {
    vector<char> inner;
    for (int ii = 0; ii < 11; ++ii) inner.push_back(' ');
    theDisplay.push_back(inner);
  }
}

TextDisplay::~TextDisplay() {}

void TextDisplay::update(board &notifier) {
  nextBlock = board.getNextBlock();
  currScore = board.getScore();
  highScore = board.getHighScore();
  level = board.getLevel();
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  out << "Level:	  " << td.level << endl;
  out << "Score:	  " << td.currScore << endl;
  out << "High Score: " << td.highScore << endl;
  for (int i = 0; i < 15; ++i) {
    out << " |";
    for (int ii = 0; ii < 11; ++ii) out << td.theDisplay[i][ii];
    out << "|" << endl;
  }
  return out;
}