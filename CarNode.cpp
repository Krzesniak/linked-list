//
// Created by peter on 22.01.2022.
//

#include "CarNode.h"

Car *CarNode::getCar() const {
    return car;
}

void CarNode::setCar(Car *car) {
    CarNode::car = car;
}

CarNode *CarNode::getNext() const {
    return next;
}

void CarNode::setNext(CarNode *next) {
    CarNode::next = next;
}

CarNode::CarNode(Car *car, CarNode *next) : car(car), next(next) {}
