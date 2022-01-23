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
public:
    void addCar();
    bool deleteCar();
    bool saveToFile();
    bool readFromFile(string fileName);
    CarNode* findCarByBrand(const string& brand);
    void printDatabase();
    void printOneByOne();
    void clearDatabase();
    void sortDatabase();

};


#endif //CAR_APPLICATION_H
