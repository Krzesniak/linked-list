//
// Created by peter on 22.01.2022.
//

#include <iostream>
#include "Application.h"

void Application::addCar() {
    string type, brand, model;
    int mileage, engineCapacity;
    float price;

    cout << "Dodawanie elementu do bazy" << endl;
    cout << "Podaj typ nadwozia auta: ";
    getline(cin, type);

    cout << "Podaj nazwe marki auta: ";
    getline(cin, brand);

    cout << "Podaj model auta: ";
    getline(cin, model);

    do {
        cout << "Podaj przebieg auta:";
        cin >> mileage;
    } while (mileage <= 0);

    do {
        cout << "Podaj cene auta:";
        cin >> price;
    } while (price <= 0);

    do {
        cout << "Podaj pojemnosc silnika auta:";
        cin >> engineCapacity;
    } while (engineCapacity < 0);
    cin.ignore();
    Car *car = new Car(type, brand, model, mileage, engineCapacity, price);
    this->carDataBase.add(car);
    cout << "Wszystkie dane zostaly dodane" << endl;

}

void Application::printDatabase() {
    cout << "Liczba wypelnionych rekordow: " << this->carDataBase.size();
    cout << "\nBAZA DANYCH: " << endl;
    carDataBase.printAll();

}

bool Application::deleteCar() {
    cout << "USUWANIE SAMOCHODU " << endl;
    int index;
    do {
        cout << "\nPodaj indeks usuwanego elementu: " << endl;
        cin >> index;
    } while (index < 0);
    return this->carDataBase.remove(index);
}

bool Application::saveToFile() {
    cout << "ZAPISYWANIE DO PLIKU " << endl;
    return this->carDataBase.saveToFile("file.txt");
}

bool Application::readFromFile(string fileName) {
    return this->carDataBase.readFromFile(fileName);
}

CarNode *Application::findCarByBrand(const string &brand) {
    this->foundElements = stack<CarNode *>();
    cout << "-------- SZUKANIE SAMOCHODU PO MARCE  --------" << endl;
    CarNode* carNode = nullptr;
    string userChoice;
    while (true) {
        if (!foundElements.empty()) {
            cout << "Nastepny element wpisz 'n', a poprzedni wpisz 'p'" << endl;
            do {
                cin >> userChoice;
            } while (!validInput(userChoice, "n", "p"));
            if (userChoice == "n") {
                auto tmpCarNode = carNode;
                carNode = this->carDataBase.findCarByBrand(brand, tmpCarNode->getNext());
                this->foundElements.push(tmpCarNode);
            } else {
                auto tmpCarNode = foundElements.top();
                this->foundElements.pop();
                carNode = this->carDataBase.findCarByBrand(brand, tmpCarNode);
            }
        } else {
            if(carNode == nullptr){
                carNode = this->carDataBase.findCarByBrand(brand, this->carDataBase.getCarNode(0));
            } else{
                auto tmpCarNode = carNode;
                carNode = this->carDataBase.findCarByBrand(brand, tmpCarNode->getNext());
                this->foundElements.push(tmpCarNode);
            }
        }
        if(carNode == nullptr) {
           break;
        }
        cout << "ZNALEZIONO PONIZSZY SAMOCHOD " << endl;
        carNode->getCar()->print();

        cout << "SZUKAC DALEJ? Wpisz 'y', jezeli tak, 'n' jezeli nie: ";
        do {
            cin >> userChoice;
        } while (!validInput(userChoice, "n", "y"));
        if(userChoice == "n") break;
    }
    cout << "Nie znaleziono wiecej wynikow lub zakonczono przeszukiwanie!";
    return carNode;
}

bool Application::validInput(const string &userChoice, const string &validOptionA, const string &validOptionB) {
    if (userChoice == validOptionA || userChoice == validOptionB) return true;
    return false;
}

void Application::printOneByOne() {
    bool firstInvoke = true;
    cout << "------- SZUKANIE POJEDYNCZEGO ELEMENTU --------" << endl;
    int index = 0;
    this->carDataBase.printOneByOne(0)->getCar()->print();
    while (true) {
        if (!firstInvoke) this->carDataBase.printOneByOne(index)->getCar()->print();
        firstInvoke = false;
        cout << "SZUKAC DALEJ? Wpisz 'y', jezeli tak, 'n' jezeli nie: ";
        string userChoice;
        do {
            cin >> userChoice;
        } while (!validInput(userChoice, "y", "n"));
        if (userChoice == "n") break;
        if (index == 0 && carDataBase.size() > 0) {
            cout << "Nastepny element wpisz 'n'";
            do {
                cin >> userChoice;
            } while (!validInput(userChoice, "-0b", "n"));
            if (userChoice == "n") index++;
        } else if (index > 0 && index < carDataBase.size() - 1) {
            cout << "Nastepny element wpisz 'n', a poprzedni wpisz 'p'";
            do {
                cin >> userChoice;
            } while (!validInput(userChoice, "p", "n"));
            if (userChoice == "n") index++;
            else if (userChoice == "p") index--;
        } else if (index > 0 && index == carDataBase.size() - 1) {
            cout << "Poprzedni element wpisz 'p'";
            do {
                cin >> userChoice;
            } while (!validInput(userChoice, "-0b", "p"));
            if (userChoice == "p") index--;
        }
    }
}

void Application::sortDatabase() {
    this->carDataBase.sortElements();
}
