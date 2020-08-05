#ifndef _OBSERVER_
#define _OBSERVER_

class Board;
class Controller;

class Observer {
public:
  Observer(){};
  virtual void update() = 0;
  virtual void poll(){};
  virtual ~Observer() = default;
  Controller *controller_;
  Board *board_;
};

#endif
