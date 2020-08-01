#include "subject.h"
#include "observer.h"

void Subject::subscribe(Observer* newObs) { observers_.insert(newObs); }

void Subject::unsubscribe(Observer* formerView) {
  observers_.erase(formerView);
}

void Subject::notifyObservers() {
  for (auto i : observers_) i->update();
}
