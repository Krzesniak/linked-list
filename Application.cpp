//
// Created by peter on 22.01.2022.
//

#include <iostream>
#include "Application.h"

void Application::addCar() {
    string type, brand, model;
    int mileage, engineCapacity;
    float price;

    cin.ignore();
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
    cout << "--------- USUWANIE SAMOCHODU --------- " << endl;
    int index;
    string userChoice;
    do {
        cout << "\nPodaj indeks usuwanego elementu: " << endl;
        cin >> index;
    } while (index < 0);
    CarNode *foundCar = this->carDataBase.getCarNode(index);
    if(foundCar == nullptr){
        cout << "Nie istnieje auto o podanym indeksie " << endl;
        return false;
    }
    cout << "Znaleziono ponizszy samochod " << endl;
    foundCar->getCar()->print();
    cout << "Aby usunac element wpisz 't', aby zostawic wpisz 'n'" << endl;
    do {
        cin >> userChoice;
    } while (!validInput(userChoice, "n", "t"));
    if(userChoice == "n"){
        cout << "Samochod nie zostal usuniety" << endl;
        return false;
    }
    else {
        this->carDataBase.remove(index);
        cout << "Samochod zostal usuniety " << endl;
        return true;
    }

}

bool Application::saveToFile() {
    string filename;
    cout << "---------  ZAPISYWANIE DO PLIKU --------- " << endl;
    cout << "Podaj nazwe pliku " << endl;
    cin >> filename;
    return this->carDataBase.saveToFile(filename);
}

bool Application::readFromFile() {
    string filename;
    cout << "--------- WCZYTYWANIE DANYCH Z PLIKU --------- " << endl;
    cout << "Podaj nazwe pliku " << endl;
    cin >> filename;
    return this->carDataBase.readFromFile(filename);
}

CarNode *Application::findCarByBrand() {
    this->foundElements = stack<CarNode *>();
    string brand;
    cout << "-------- SZUKANIE SAMOCHODU PO MARCE  --------" << endl;
    cout << "Podaj haslo kluczowe do szukania: ";
    cin >> brand;
    string userChoice;
    CarNode *carNode = nullptr;
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
            if (carNode == nullptr) {
                carNode = this->carDataBase.findCarByBrand(brand, this->carDataBase.getCarNode(0));
            } else {
                auto tmpCarNode = carNode;
                carNode = this->carDataBase.findCarByBrand(brand, tmpCarNode->getNext());
                this->foundElements.push(tmpCarNode);
            }
        }
        if (carNode == nullptr) {
            break;
        }
        cout << "ZNALEZIONO PONIZSZY SAMOCHOD " << endl;
        carNode->getCar()->print();

        cout << "SZUKAC DALEJ? Wpisz 'y', jezeli tak, 'n' jezeli nie: ";
        do {
            cin >> userChoice;
        } while (!validInput(userChoice, "n", "y"));
        if (userChoice == "n") break;
    }
    cout << "Nie znaleziono wiecej wynikow lub zakonczono przeszukiwanie!" << endl;
    return carNode;
}

bool Application::validInput(const string &userChoice, const string &validOptionA, const string &validOptionB) {
    if (userChoice == validOptionA || userChoice == validOptionB) return true;
    return false;
}

void Application::printOneByOne() {
    bool firstInvoke = true;
    cout << "------- SZUKANIE POJEDYNCZEGO ELEMENTU --------" << endl;
    if(this->carDataBase.size() == 0) {
        cout << "BRAK WYNIKOW " << endl;
        return;
    }
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
    cout << "----------- SORTOWANIE ELEMENTOW PO MARCE ----------" << endl;
    this->carDataBase.sortElements();
}
void Application::clearDatabase() {
    cout << "----------- CZYSZCZENIE BAZY DANYCH ----------" << endl;
    this->carDataBase.clearAll();
}

bool Application::menu() {
    bool applicationWorking = true;
    string userChoice;
    cout << "---------- MENU GLOWNE APLIKACJI ---------" << endl;
    cout << "1. Wyswietl cala baze danych " << endl;
    cout << "2. Wyswietl baze danych pojedynczo " << endl;
    cout << "3. Wczytaj baze danych z pliku " << endl;
    cout << "4. Zapisz baze danych do pliku " << endl;
    cout << "5. Dodaj samochod do bazy danych " << endl;
    cout << "6. Usun samochod z bazy danych " << endl;
    cout << "7. Szukaj samochod z bazy danych po nazwie marki " << endl;
    cout << "8. Szukaj samochod z bazy danych po cenie " << endl;
    cout << "9. Posortuj samochody po cenie " << endl;
    cout << "10. Wyczysc baze danych " << endl;
    cout << "11. Wyjscie z programu " << endl;
    cout << "Twoj wybor: ";
    do {
        cin >> userChoice;
    } while (!isInputDigit(userChoice));

    int userChoiceInt = atoi(userChoice.c_str());
    switch (userChoiceInt) {
        case 1: {
            this->printDatabase();
            break;
        }
        case 2: {
            this->printOneByOne();
            break;
        }
        case 3: {
            this->readFromFile();
            break;
        }
        case 4: {
            this->saveToFile();
            break;
        }
        case 5: {
            this->addCar();
            break;
        }
        case 6: {
            this->deleteCar();
            break;
        }
        case 7: {
            this->findCarByBrand();
            break;
        }
        case 8 :{
           this->findCarByPrice();
            break;
        }
        case 9: {
            this->sortDatabase();
            break;
        }
        case 10: {
            this->clearDatabase();
            break;
        }
        default: {
            applicationWorking = false;
            break;
        }

    }
    return applicationWorking;
}

bool Application::isInputDigit(const string &str) {
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

void Application::findCarByPrice() {
    this->foundElements = stack<CarNode *>();
    string brand;
    cout << "-------- SZUKANIE SAMOCHODU PO CENIE  --------" << endl;
    string userChoice;
    int min, max;
    do {
        cout << "Podaj wartosc minimalna: "; cin >> userChoice;
        if(!isInputDigit(userChoice)) continue;
        else min = atoi(userChoice.c_str());
        cout << "Podaj wartosc maksymalna: "; cin >> userChoice;
        if(isInputDigit(userChoice)){
            max = atoi(userChoice.c_str());
            break;
        }
    } while (true);
    CarNode *carNode = nullptr;
    while (true) {
        if (!foundElements.empty()) {
            cout << "Nastepny element wpisz 'n', a poprzedni wpisz 'p'" << endl;
            do {
                cin >> userChoice;
            } while (!validInput(userChoice, "n", "p"));
            if (userChoice == "n") {
                auto tmpCarNode = carNode;
                carNode = this->carDataBase.findCarByPrice(min, max, tmpCarNode->getNext());
                this->foundElements.push(tmpCarNode);
            } else {
                auto tmpCarNode = foundElements.top();
                this->foundElements.pop();
                carNode = this->carDataBase.findCarByPrice(min, max, tmpCarNode);
            }
        } else {
            if (carNode == nullptr) {
                carNode = this->carDataBase.findCarByPrice(min, max, this->carDataBase.getCarNode(0));
            } else {
                auto tmpCarNode = carNode;
                carNode = this->carDataBase.findCarByPrice(min, max, tmpCarNode->getNext());
                this->foundElements.push(tmpCarNode);
            }
        }
        if (carNode == nullptr) {
            break;
        }
        cout << "ZNALEZIONO PONIZSZY SAMOCHOD " << endl;
        carNode->getCar()->print();

        cout << "SZUKAC DALEJ? Wpisz 'y', jezeli tak, 'n' jezeli nie: ";
        do {
            cin >> userChoice;
        } while (!validInput(userChoice, "n", "y"));
        if (userChoice == "n") break;
    }
    cout << "Nie znaleziono wiecej wynikow lub zakonczono przeszukiwanie!" << endl;

}


