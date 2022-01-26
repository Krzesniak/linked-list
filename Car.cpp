//
// Created by peter on 22.01.2022.
//

#include <iostream>
#include <iomanip>
#include "Car.h"

const string &Car::getType() const {
    return type;
}

void Car::setType(const string &type) {
    Car::type = type;
}

const string &Car::getBrand() const {
    return brand;
}

void Car::setBrand(const string &brand) {
    Car::brand = brand;
}

const string &Car::getModel() const {
    return model;
}

void Car::setModel(const string &model) {
    Car::model = model;
}

int Car::getMileage() const {
    return mileage;
}

void Car::setMileage(int mileage) {
    Car::mileage = mileage;
}

int Car::getEngingeCapacity() const {
    return engineCapacity;
}

void Car::setEngingeCapacity(int engingeCapacity) {
    Car::engineCapacity = engingeCapacity;
}

float Car::getPrice() const {
    return price;
}

void Car::setPrice(float price) {
    Car::price = price;
}

Car::Car(const string &type, const string &brand, const string &model, int mileage, int engineCapacity, float price)
        : type(type), brand(brand), model(model), mileage(mileage), engineCapacity(engineCapacity), price(price) {}

void Car::print() const {
    cout << std::setw(20) << std::left << "TYP_NADWOZIA:" << std::setw(50) << type << endl;
    cout << std::setw(20) << std::left << "MARKA:" << std::setw(50) << brand << endl;
    cout << std::setw(20) << std::left << "MODEL:" << std::setw(50) << model << endl;
    cout << std::setw(20) << std::left << "PRZEBIEG:" << std::setw(50) << mileage << endl;
    cout << std::setw(20) << std::left << "CENA:" << std::setw(50) << price << endl;
    cout << std::setw(20) << std::left << "POJEMNOSC_SILNIKA:" << std::setw(50) << engineCapacity << endl << endl;

}
