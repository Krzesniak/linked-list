//
// Created by peter on 22.01.2022.
//

#ifndef CAR_H
#define CAR_H

#include <string>

using namespace std;
class Car {
    string type, brand, model;
    int mileage, engineCapacity;
    float price;
public:
    Car(const string &type, const string &brand, const string &model, int mileage, int engineCapacity, float price);

    const string &getType() const;

    void setType(const string &type);

    const string &getBrand() const;

    void setBrand(const string &brand);

    const string &getModel() const;

    void setModel(const string &model);

    int getMileage() const;

    void setMileage(int mileage);

    int getEngingeCapacity() const;

    void setEngingeCapacity(int engingeCapacity);

    float getPrice() const;

    void setPrice(float price);

    void print() const;
};


#endif //CAR_H
