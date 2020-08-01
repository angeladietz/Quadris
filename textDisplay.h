#ifndef _TEXTDISPLAY_
#define _TEXTDISPLAY_

#include <iostream>
#include <vector>

#include "board.h"
#include "commandInterpreter.h"
#include "observer.h"
#include "controller.h"

class TextDisplay : public Observer {
  
  Controller *controller_;
  Board *board_;
  Block *nextBlock;
  int currScore;
  int highScore;
  int level;

 public:
  TextDisplay(Board*, Controller*);
  ~TextDisplay();
  void update() override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
