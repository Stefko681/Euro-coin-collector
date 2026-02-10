//
// Created by stefko on 2/9/26.
//

#ifndef EURO_COIN_COLLECTOR_COINS_H
#define EURO_COIN_COLLECTOR_COINS_H

const int COINS_COUNT = 8;
const int COUNTRIES_COUNT = 25;
const int BUFFER = 1000;

struct country {
    char *name;
    bool coins[COINS_COUNT];
    int collectedCount;
};

int strLen(const char *str);

char *strCopy(const char *source, char *dest);

bool strCmp(const char *str1, const char *str2);

void inputCountries(country *&countries);

void printMenu();

void printAddCoinMenu();

const char *valueStr(const int n);

void printNSpaces(int n);

void readFile(country *&countries);

void freeMemoryFromCountries(country *&countries);

int readInt();

void addCoin(country *&countries);

void viewCollectionMatrix(country *&countries);

void detailedStatistics(country *&countries);

void saveAndExit(country *&countries);

void mainLoop();

#endif //EURO_COIN_COLLECTOR_COINS_H
