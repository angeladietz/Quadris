#ifndef _TEXTDISPLAY_
#define _TEXTDISPLAY_

#include <iostream>
#include <vector>

#include "board.h"
#include "commandInterpreter.h"
#include "controller.h"
#include "observer.h"

class TextDisplay : public Observer {
public:
  TextDisplay(Board *, Controller *);
  ~TextDisplay();
  void update() override;
  void poll() override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

private:
  void print();
  void printBlock(BlockType);
  Controller *controller_;
  Board *board_;
  BlockType nextBlock_;
  int currScore_;
  int highScore_;
  int level_;
  bool isGameOver_;
};

#endif
