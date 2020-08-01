#ifndef _TEXTDISPLAY_
#define _TEXTDISPLAY_

#include <iostream>
#include <vector>

#include "observer.h"

class TextDisplay : public Observer {
std::vector<std::vector<char>> theDisplay;

 public:
  TextDisplay();
  ~TextDisplay();
  void update();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
