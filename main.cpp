#include <iostream>

#include <string>
#include <fstream>
#include <iomanip>
#include <stack>

using namespace std;
class Car {
    string type, brand, model;
    int mileage, engineCapacity;
    float price;
public:
    const string &getType() const {
        return type;
    }

    void setType(const string &type) {
        Car::type = type;
    }

    const string &getBrand() const {
        return brand;
    }

    void setBrand(const string &brand) {
        Car::brand = brand;
    }

    const string &getModel() const {
        return model;
    }

    void setModel(const string &model) {
        Car::model = model;
    }

    int getMileage() const {
        return mileage;
    }

    void setMileage(int mileage) {
        Car::mileage = mileage;
    }

    int getEngingeCapacity() const {
        return engineCapacity;
    }

    void setEngingeCapacity(int engingeCapacity) {
        Car::engineCapacity = engingeCapacity;
    }

    float getPrice() const {
        return price;
    }

    void setPrice(float price) {
        Car::price = price;
    }

    Car(const string &type, const string &brand, const string &model, int mileage, int engineCapacity, float price)
            : type(type), brand(brand), model(model), mileage(mileage), engineCapacity(engineCapacity), price(price) {}

    void print() const {
        cout << std::setw(20) << std::left << "TYP_NADWOZIA:" << std::setw(50) << type << endl;
        cout << std::setw(20) << std::left << "MARKA:" << std::setw(50) << brand << endl;
        cout << std::setw(20) << std::left << "MODEL:" << std::setw(50) << model << endl;
        cout << std::setw(20) << std::left << "PRZEBIEG:" << std::setw(50) << mileage << endl;
        cout << std::setw(20) << std::left << "CENA:" << std::setw(50) << price << endl;
        cout << std::setw(20) << std::left << "POJEMNOSC_SILNIKA:" << std::setw(50) << engineCapacity << endl << endl;

    }

};

class CarNode {
    Car *car;
    CarNode *next;
public:
    CarNode(Car *car, CarNode *next) : car(car), next(next) {}

public:
    Car *getCar() const {
        return car;
    }

    void setCar(Car *car) {
        this->car = car;
    }

    CarNode *getNext() const {
        return next;
    }

    void setNext(CarNode *next) {
        CarNode::next = next;
    }

};


class SortingLinkedList {
public:
    void swap(CarNode *a, CarNode *b) {
        auto temp = a->getCar();
        a->setCar(b->getCar());
        b->setCar(temp);
    }

    void bubbleSort(CarNode *start) {
        int swapped, i;
        CarNode *ptr1;
        CarNode *lptr = nullptr;

        if (start == nullptr)
            return;
        do
        {
            swapped = 0;
            ptr1 = start;

            while (ptr1->getNext() != lptr)
            {
                if (ptr1->getCar()->getPrice() > ptr1->getNext()->getCar()->getPrice())
                {
                    swap(ptr1, ptr1->getNext());
                    swapped = 1;
                }
                ptr1 = ptr1->getNext();
            }
            lptr = ptr1;
        }
        while (swapped);

    }
};

class CarDataBase {
    CarNode *head;
    string fileName;
    SortingLinkedList sortingLinkedList;
public:

    CarNode *getCarNode(unsigned int number) {
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

    int size() {
        CarNode *carNode = this->head;
        int counter = 0;
        while (carNode != nullptr) {
            counter++;
            carNode = carNode->getNext();
        }
        return counter;
    }

    void printAll() {
        CarNode *carNode = this->head;
        int counter = 1;
        while (carNode != nullptr) {
            std::cout << "NUMER AUTA: " << counter << ". " << std::endl;
            carNode->getCar()->print();
            carNode = carNode->getNext();
            counter++;
        }

    }

    void add(Car *car) {
        auto *newNode = new CarNode(car, nullptr);
        if (this->size() == 0) this->head = newNode;
        else {
            CarNode *carNode = this->getCarNode(this->size() - 1);
            carNode->setNext(newNode);
        }
    }

    bool remove(unsigned int index) {
        if (this->size() <= 0 || index > this->size()) return false;
        if (index == 0 && this->size() == 1) {
            delete this->head->getCar();
            delete this->head;
            this->head = nullptr;
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

    bool saveToFile() {
        return this->saveToFile(this->fileName);
    }

    bool saveToFile(string fileName) {
        std::ofstream file = std::ofstream{fileName};
        CarNode *carNode = this->head;
        while (carNode != nullptr) {
            file << carNode->getCar()->getType() << endl;
            file << carNode->getCar()->getBrand() << endl;
            file << carNode->getCar()->getModel() << endl;
            file << carNode->getCar()->getMileage() << endl;
            file << carNode->getCar()->getPrice() << endl;
            file << carNode->getCar()->getEngingeCapacity() << endl;
            carNode = carNode->getNext();
        }
        file.close();
        return true;
    }

    bool readFromFile(string fileName) {
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

    void clearAll() {
        if(this->size() <= 0) return;
        auto allElements = this->size();
        for(int i=0; i<allElements; i++){
            this->remove(0);
        }
        this->head = nullptr;
    }

    CarNode *findCarByBrand(const string &brand, CarNode *startingNode) {
        if (brand.empty() || startingNode == nullptr) return nullptr;
        while (startingNode != nullptr) {
            if (startingNode->getCar()->getBrand().find(brand) != string::npos) return startingNode;
            startingNode = startingNode->getNext();
        }
        return nullptr;
    }

    CarNode *printOneByOne(unsigned int index) {
        return this->getCarNode(index);
    }

    CarNode *sortElements() {
        sortingLinkedList.bubbleSort(this->head);
        return this->head;
    }

    CarNode *findCarByPrice(int min, int max, CarNode *startingNode) {
        if (startingNode == nullptr) return nullptr;
        while (startingNode != nullptr) {
            if (startingNode->getCar()->getPrice() >= min && startingNode->getCar()->getPrice() <= max) return startingNode;
            startingNode = startingNode->getNext();
        }
        return nullptr;
    }
};
class Application {
    CarDataBase carDataBase;
    stack<CarNode *> foundElements;
public:

    void addCar() {
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

    void printDatabase() {
        cout << "Liczba wypelnionych rekordow: " << this->carDataBase.size();
        cout << "\nBAZA DANYCH: " << endl;
        carDataBase.printAll();

    }

    bool deleteCar() {
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

    bool saveToFile() {
        string filename;
        cout << "---------  ZAPISYWANIE DO PLIKU --------- " << endl;
        cout << "Podaj nazwe pliku " << endl;
        cin >> filename;
        return this->carDataBase.saveToFile(filename);
    }

    bool readFromFile() {
        string filename;
        cout << "--------- WCZYTYWANIE DANYCH Z PLIKU --------- " << endl;
        cout << "Podaj nazwe pliku " << endl;
        cin >> filename;
        return this->carDataBase.readFromFile(filename);
    }

    CarNode *findCarByBrand() {
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

    bool validInput(const string &userChoice, const string &validOptionA, const string &validOptionB) {
        if (userChoice == validOptionA || userChoice == validOptionB) return true;
        return false;
    }

    void printOneByOne() {
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

    void sortDatabase() {
        cout << "----------- SORTOWANIE ELEMENTOW PO MARCE ----------" << endl;
        this->carDataBase.sortElements();
    }
    void clearDatabase() {
        cout << "----------- CZYSZCZENIE BAZY DANYCH ----------" << endl;
        this->carDataBase.clearAll();
    }

    bool menu() {
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

    bool isInputDigit(const string &str) {
        for (char const &c : str) {
            if (std::isdigit(c) == 0) return false;
        }
        return true;
    }

    void findCarByPrice() {
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

};
int main() {

    Application application{};
    while ( application.menu());


}
