//
// Created by netanel on 19/01/2020.
//

#include "Point.h"

/**
*this class represents point object
 */

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}
int Point::getX() {
    return this->x;
}

int Point::getY() {
    return this->y;
}

void Point::setX(int x) {
    this->x=x;
}
void Point::setY(int y) {
    this->y=y;
}
