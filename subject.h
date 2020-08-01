#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <unordered_set>

#include "observer.h"

class Subject {
  std::unordered_set<Observer*> observers_;

 public:
  Subject();
  virtual ~Subject() = 0;
  void subscribe(Observer*);
  void unsubscribe(Observer*);
  void notifyObservers();
};

#endif
