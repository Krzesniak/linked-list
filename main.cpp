#include <iostream>
#include "Application.h"

#include <fstream>
int main() {
    Application application{};
/*    application.addCar();
    application.addCar();
    application.printDatabase();*/
    application.readFromFile("file.txt");
    application.printDatabase();
    application.sortDatabase();
    application.printDatabase();
//    application.findCarByBrand("BWM");
    application.deleteCar();
    application.printDatabase();
}
