//
// Created by stefko on 2/9/26.
//
#include <iostream>
#include <fstream>
#include "country.h"

const char *SAVE_FILE = "coins.txt";

int strLen(const char *str) {
    int index = 0;
    if (!str) {
        return -1;
    }
    while (str[index] != '\0') {
        index++;
    }
    return index;
}

char *strCopy(const char *source, char *dest) {
    int index = 0;
    while (source[index] != '\0') {
        dest[index] = source[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}

bool strCmp(const char *str1, const char *str2) {
    if (strLen(str1) != strLen(str2)) {
        return false;
    }
    int index = 0;
    while (str1[index] != '\0' && str2[index] != '\0') {
        if (str1[index] != str2[index]) {
            return false;
        }
        index++;
    }
    return true;
}

void inputCountries(country *&countries) {
    const char *countriesList[] = {
        "Austria", "Belgium", "Bulgaria", "Croatia", "Cyprus", "Estonia", "Finland", "France", "Germany", "Greece",
        "Ireland", "Italy", "Latvia", "Lithuania", "Luxembourg", "Malta", "Netherlands", "Portugal", "Slovakia",
        "Slovenia", "Spain", "Andorra", "Monaco", "San Marino", "Vatican City"
    };
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        countries[i].name = new char[strLen(countriesList[i]) + 1];
        strCopy(countriesList[i], countries[i].name);
    }
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        for (int j = 0; j < COINS_COUNT; ++j) {
            countries[i].coins[j] = false;
        }
        countries[i].collectedCount = 0;
    }
}

void printMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Mark coin as found" << std::endl;
    std::cout << "2. View collection matrix" << std::endl;
    std::cout << "3. Detailed statistics" << std::endl;
    std::cout << "4. Save & Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Choice: ";
}

void printAddCoinMenu() {
    std::cout << std::endl;
    std::cout << "Select coin denomination: " << std::endl;
    std::cout << "1. 1 cent" << std::endl;
    std::cout << "2. 2 cent" << std::endl;
    std::cout << "3. 5 cent" << std::endl;
    std::cout << "4. 10 cent" << std::endl;
    std::cout << "5. 20 cent" << std::endl;
    std::cout << "6. 50 cent" << std::endl;
    std::cout << "7. 1 euro" << std::endl;
    std::cout << "8. 2 euro" << std::endl;
    std::cout << std::endl;
    std::cout << "Choice: ";
}

const char *valueStr(const int n) {
    if (n < 7) {
        return "cent";
    }
    return "euro";
}

void printNSpaces(int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << " ";
    }
}

void readFile(country *&countries) {
    std::ifstream in(SAVE_FILE);
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        char buffer[BUFFER];
        in.getline(buffer, BUFFER, '|');
        countries[i].name = new char[strLen(buffer) + 1];
        strCopy(buffer, countries[i].name);
        for (int j = 0; j < COINS_COUNT; ++j) {
            in >> countries[i].coins[j];
        }
        in >> countries[i].collectedCount;
        in.ignore();
    }
    in.close();
}

void freeMemoryFromCountries(country *&countries) {
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        delete[] countries[i].name;
    }
    delete[] countries;
}

int readInt() {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(BUFFER, '\n');
            std::cout << ">> Invalid option! Please enter a number: ";
        } else {
            std::cin.ignore(BUFFER, '\n');
            return input;
        }
    }
}

void addCoin(country *&countries) {
    std::cout << ">> Enter country name: ";
    char buffer[BUFFER];
    std::cin.getline(buffer, BUFFER);
    int searchedIndex = -1;
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        if (strCmp(buffer, countries[i].name)) {
            searchedIndex = i;
            break;
        }
    }
    if (searchedIndex == -1) {
        std::cout << ">> Error: County not existing or not using the euro" << std::endl;
        return;
    }
    std::cout << ">> Found: " << buffer << " (" << countries[searchedIndex].collectedCount << "/8 collected)" <<
            std::endl;
    printAddCoinMenu();
    int coinValueChoice = readInt();
    int coinValue = 0;
    switch (coinValueChoice) {
        case 1: coinValue = 1;
            break;
        case 2: coinValue = 2;
            break;
        case 3: coinValue = 5;
            break;
        case 4: coinValue = 10;
            break;
        case 5: coinValue = 20;
            break;
        case 6: coinValue = 50;
            break;
        case 7: coinValue = 1;
            break;
        case 8: coinValue = 2;
            break;
        default: std::cout << "Error: Invalid option!" << std::endl;
            return;
    }
    if (countries[searchedIndex].coins[coinValueChoice - 1] == true) {
        std::cout << ">> You already have this coin!" << std::endl;
        return;
    }
    countries[searchedIndex].coins[coinValueChoice - 1] = true;
    std::cout << std::endl;
    std::cout << ">> Success! You marked [" << coinValue << " " << valueStr(coinValueChoice) << "] from " << buffer
            <<
            " as COLLECTED." << std::endl;
    countries[searchedIndex].collectedCount++;
    std::cout << ">> " << buffer << " progress: " << countries[searchedIndex].collectedCount << "/8." << std::endl;
    std::cout << std::endl;
}

void viewCollectionMatrix(country *&countries) {
    std::cout << std::endl;
    std::cout << "Country";
    printNSpaces(7);
    std::cout << "| 1c | 2c | 5c | 10c | 20c | 50c | 1€ | 2€ | Total" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        std::cout << countries[i].name;
        printNSpaces(14 - strLen(countries[i].name));
        std::cout << "|";
        for (int j = 0; j < COINS_COUNT; ++j) {
            std::cout << " [";
            if (countries[i].coins[j]) { std::cout << 'X'; } else { std::cout << " "; }
            if (j < 3) {
                std::cout << "]|";
            } else if (j < 6) {
                std::cout << "] |";
            } else {
                std::cout << "]|";
            }
        }
        std::cout << "  ";
        if (countries[i].collectedCount == 8) { std::cout << " DONE!" << std::endl; } else {
            std::cout << countries[i].collectedCount << "/8" << std::endl;
        }
    }
    std::cout << std::endl;
}

void detailedStatistics(country *&countries) {
    std::cout << std::endl;
    std::cout << "--- Collection stats ---" << std::endl;
    double collectionCount = 0.0;
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        for (int j = 0; j < COINS_COUNT; ++j) {
            if (countries[i].coins[j] == true) {
                collectionCount++;
            }
        }
    }
    std::cout << "Total coins collected: " << collectionCount << " / 200" << std::endl;
    std::cout << "Completion: " << (collectionCount * 100.0) / 200.0 << "%" << std::endl;
    std::cout << std::endl;
    std::cout << "Top countries:" << std::endl;
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        for (int j = 1; j < COUNTRIES_COUNT - 1; ++j) {
            if (countries[j].collectedCount > countries[i].collectedCount) {
                country temp = countries[i];
                countries[i] = countries[j];
                countries[j] = temp;
            }
        }
        std::cout << i + 1 << ". " << countries[i].name << " (" << countries[i].collectedCount << "/8)" <<
                std::endl;
    }
    std::cout << std::endl;
}

void saveAndExit(country *&countries) {
    std::ofstream out(SAVE_FILE);
    if (!out.is_open()) {
        std::cout << ">> Error: File could not be created!" << std::endl;
        return;
    }
    for (int i = 0; i < COUNTRIES_COUNT; ++i) {
        char buffer[BUFFER];
        out << countries[i].name << "|";
        for (int j = 0; j < COINS_COUNT; ++j) {
            out << countries[i].coins[j] << " ";
        }
        out << countries[i].collectedCount << std::endl;
    }
    out.close();
    std::cout << ">> Data saved to " << SAVE_FILE << std::endl;
    std::cout << ">> GoodBye!" << std::endl;
}

void mainLoop() {
    country *countries = new country[COUNTRIES_COUNT];
    std::ifstream in(SAVE_FILE);
    std::cout << ">> Loading data..." << std::endl;
    if (!in.is_open()) {
        std::cout << ">> File not found. Initializing new collection with 25 countries." << std::endl;
        inputCountries(countries);
    } else {
        readFile(countries);
    }
    std::cout << ">> Welcome to euro coin collector!" << std::endl;
    std::cout << std::endl;
    int menuOption = 0;
    do {
        printMenu();
        menuOption = readInt();
        switch (menuOption) {
            case 1: addCoin(countries);
                break;
            case 2: viewCollectionMatrix(countries);
                break;
            case 3: detailedStatistics(countries);
                break;
            case 4: saveAndExit(countries);
                break;
            default: std::cout << ">> Invalid option!" << std::endl;
                break;
        }
    } while (menuOption != 4);
    freeMemoryFromCountries(countries);
}
