#include "textDisplay.h"

using namespace std;

#include <iostream>
#include <vector>

TextDisplay::TextDisplay() {
  for (int i = 0; i < 15; ++i) {
    vector<char> inner;
    for (int ii = 0; ii < 11; ++ii) inner.push_back(' ');
    theDisplay.push_back(inner);
  }
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 15; ++i) {
    out << " |";
    for (int ii = 0; ii < 11; ++ii) out << td.theDisplay[i][ii];
    out << "|" << endl;
  }
  return out;
}