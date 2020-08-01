#include "subject.h"

#include <set>

#include "observer.h"

void Subject::subscribe(Observer* newObs) { _observers.insert(newObs); }

void Subject::unsubscribe(Observer* formerView) {
  _observers.erase(formerView);
}

void Subject::notifyObservers() {
  for (auto i : _observers) i->update();
}
