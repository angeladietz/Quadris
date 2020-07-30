#ifndef _OBSERVER_
#define _OBSERVER_

class Observer {
 public:
  Observer();
  virtual void update() = 0;
  virtual ~Observer() = default;
};

#endif
