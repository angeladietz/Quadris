#include "location.h"

Location::Location(int x, int y): x_(x), y_(y) {}

int Location::getX() { return x_; }

int Location::getY() { return y_; }

void Location::setX(int x) { x_ = x; }

void Location::setY(int y) { y_ = y; }
