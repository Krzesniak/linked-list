//
// Created by peter on 22.01.2022.
//

#ifndef CAR_CARDATABASE_H
#define CAR_CARDATABASE_H


#include "Car.h"
#include "CarNode.h"

#include "SortingLinkedList.h"

class CarDataBase{
    CarNode* head;
    string fileName;
    SortingLinkedList sortingLinkedList;

    CarNode* recursiveFindingBrand();
public:
    int size();
    void printAll();
    CarNode* printOneByOne(unsigned int index);
    void clearAll();
    bool saveToFile();
    bool saveToFile(string fileName);
    bool readFromFile(string fileName);
    void readFromFile();
    void add(Car* car) ;
    bool remove(unsigned int index);
    CarNode* getCarNode(unsigned int number);
    CarNode* sortElements();
    CarNode *findCarByBrand(const string &brand, CarNode *startingNode);
};


#endif //CAR_CARDATABASE_H
