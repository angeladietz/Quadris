#ifndef _TEXTDISPLAY_
#define _TEXTDISPLAY_

#include <iostream>
#include <vector>

#include "board.h"
#include "commandInterpreter.h"
#include "observer.h"

class TextDisplay : public Observer {
  std::vector<std::vector<char>> theDisplay;
  commandInterpreter *command;
  Block *nextBlock;
  int currScore;
  int highScore;
  int level;

  void read();

 public:
  TextDisplay();
  ~TextDisplay();
  void update(board &);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
