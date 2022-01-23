//
// Created by peter on 22.01.2022.
//

#ifndef CAR_CARNODE_H
#define CAR_CARNODE_H


#include "Car.h"

class CarNode {
    Car* car;
    CarNode* next;
public:
    CarNode(Car *car, CarNode *next);

public:
    Car *getCar() const;

    void setCar(Car *car);

    CarNode *getNext() const;

    void setNext(CarNode *next);
};


#endif //CAR_CARNODE_H
