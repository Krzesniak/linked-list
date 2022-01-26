//
// Created by peter on 22.01.2022.
//

#ifndef CAR_APPLICATION_H
#define CAR_APPLICATION_H


#include "CarDataBase.h"

#include <stack>
using namespace std;
class Application {
    CarDataBase carDataBase;
    stack<CarNode*> foundElements;

    static bool validInput(const string& input, const string& validOptionA, const string& validOptionB);
    static bool isInputDigit(const string & str);
public:
    void addCar();
    bool deleteCar();
    bool saveToFile();
    bool readFromFile();
    CarNode* findCarByBrand();
    void printDatabase();
    void printOneByOne();
    void clearDatabase();
    void sortDatabase();
    bool menu();

    void findCarByPrice();
};


#endif //CAR_APPLICATION_H
