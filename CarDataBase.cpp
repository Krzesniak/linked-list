//
// Created by peter on 22.01.2022.
//

#include <fstream>
#include <iostream>
#include "CarDataBase.h"


CarNode *CarDataBase::getCarNode(unsigned int number) {
    if (number > this->size()) return nullptr;
    CarNode *carNode = this->head;
    int counter = 0;
    while (carNode != nullptr) {
        if (counter == number) return carNode;
        carNode = carNode->getNext();
        counter++;
    }
    return carNode;
}

int CarDataBase::size() {
    CarNode *carNode = this->head;
    int counter = 0;
    while (carNode != nullptr) {
        counter++;
        carNode = carNode->getNext();
    }
    return counter;
}

void CarDataBase::printAll() {
    CarNode *carNode = this->head;
    int counter = 1;
    while (carNode != nullptr) {
        std::cout << "NUMER AUTA: " << counter << ". " << std::endl;
        carNode->getCar()->print();
        carNode = carNode->getNext();
        counter++;
    }

}

void CarDataBase::add(Car *car) {
    auto *newNode = new CarNode(car, nullptr);
    if (this->size() == 0) this->head = newNode;
    else {
        CarNode *carNode = this->getCarNode(this->size() - 1);
        carNode->setNext(newNode);
    }
}

bool CarDataBase::remove(unsigned int index) {
    if (this->size() <= 0 || index > this->size()) return false;
    if (index == 0 && this->size() == 1) {
        delete this->head->getCar();
        delete this->head;
        return true;

    } else if (index == 0 && this->size() > 1) {
        auto tmp = this->head;
        this->head = this->head->getNext();
        delete tmp->getCar();
        delete tmp;
        return true;

    } else if (index == this->size() - 1) {
        CarNode *previous = this->getCarNode(index - 1);
        CarNode *current = this->getCarNode(index);
        previous->setNext(nullptr);
        delete current->getCar();
        delete current;
        return true;

    } else {
        CarNode *previous = this->getCarNode(index - 1);
        CarNode *toRemove = this->getCarNode(index);
        CarNode *nextOne = this->getCarNode(index + 1);
        previous->setNext(nextOne);
        delete toRemove->getCar();
        delete toRemove;
        return true;
    }
}

bool CarDataBase::saveToFile() {
    return this->saveToFile(this->fileName);
}

bool CarDataBase::saveToFile(string fileName) {
    std::ofstream file = std::ofstream{fileName};
    CarNode *carNode = this->head;
    while (carNode != nullptr) {
        file << carNode->getCar()->getType() << endl;
        file << carNode->getCar()->getBrand() << endl;
        file << carNode->getCar()->getModel() << endl;
        file << carNode->getCar()->getMileage() << endl;
        file << carNode->getCar()->getEngingeCapacity();
        carNode = carNode->getNext();
    }
    file.close();
    return true;
}

bool CarDataBase::readFromFile(string fileName) {
    this->clearAll();
    fstream file;
    file.open(fileName, ios::in);
    if (!file.good()) return false;
    string line;
    int lineNumber = 0;
    string type, brand, model;
    int mileage, engineCapacity;
    float price;
    while (getline(file, line)) {
        switch (lineNumber) {
            case 0:
                type = line;
                break;
            case 1:
                brand = line;
                break;
            case 2:
                model = line;
                break;
            case 3:
                mileage = atoi(line.c_str());
                break;
            case 4:
                price = atof(line.c_str());
                break;
            case 5:
                engineCapacity = atoi(line.c_str());
                break;
            default:
                break;
        }
        lineNumber++;
        if (lineNumber == 6) {
            Car *car = new Car(type, brand, model, mileage, engineCapacity, price);
            this->add(car);
            lineNumber = 0;
        }
    }
    return true;
}

void CarDataBase::clearAll() {
    return;
}

CarNode *CarDataBase::findCarByBrand(const string &brand, CarNode *startingNode) {
    if (brand.empty() || startingNode == nullptr) return nullptr;
    while (startingNode != nullptr) {
        if (startingNode->getCar()->getBrand().find(brand) != string::npos) return startingNode;
        startingNode = startingNode->getNext();
    }
    return nullptr;
}

CarNode *CarDataBase::recursiveFindingBrand() {
    return nullptr;
}

CarNode*  CarDataBase::printOneByOne(unsigned int index) {
    return this->getCarNode(index);
}

CarNode *CarDataBase::sortElements() {
    sortingLinkedList.bubbleSort(this->head);
    return this->head;
}


