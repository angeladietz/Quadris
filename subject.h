#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <unordered_set>
#include "observer.h"

class Subject {
  std::unordered_set<Observer*> observers;

 public:
  Subject();
  void subscribe(Observer*);
  void unsubscribe(Observer*);
  void notifyObservers();
  virtual ~Subject()=0;
};

#endif
