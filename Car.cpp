//
// Created by peter on 22.01.2022.
//

#include <iostream>
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
void Car::print() const{
    cout << "TYP NADWOZIA:			\t\t" << type << endl;
    cout << "MARKA:					\t" << brand << endl;
    cout << "MODEL:					\t" << model << endl;
    cout << "PRZEBIEG:				\t" << mileage << endl;
    cout << "CENA:					\t" << price << endl;
    cout << "POJEMNOSC SILNIKA:		\t\t" << engineCapacity << endl << endl;

}
