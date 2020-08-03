#ifndef _OBSERVER_
#define _OBSERVER_

class Board;

class Observer {
 public:
  Observer() {};
  virtual void update() = 0;
  virtual void poll() {};
  virtual ~Observer() = default;
};

#endif
