# Euro Coin Collector 🪙

A console-based C++ application designed for numismatists to track their collection of Euro coins across all Eurozone countries.

## 📋 Overview

This application helps collectors manage their progress in finding all 8 standard Euro coin denominations (1c to 2€) for every country that issues them. It features a visual matrix of the collection, detailed completion statistics, and persistent data storage.

## 🚀 Key Features

* **Collection Tracking:**
    * Support for **25 Countries** (including microstates like Vatican City, Monaco, San Marino).
    * Track all **8 Denominations** per country: 1c, 2c, 5c, 10c, 20c, 50c, 1€, 2€.
    * Mark found coins interactively.
* **Visual Matrix:**
    * Displays a formatted table showing the status of every coin for every country.
    * Uses `[X]` for collected coins and `[ ]` for missing ones.
* **Statistics:**
    * Calculates total completion percentage.
    * Ranks countries based on the number of coins collected.
* **Persistence:**
    * Automatically initializes the database on the first run.
    * Saves and loads progress from `coins.txt` ensuring no data is lost.

## 🛠️ Technical Implementation

The project is built with **C++20** and focuses on structured data management:

* **Data Structures:**
    * Usage of `struct` to represent countries, containing dynamic name arrays and fixed boolean arrays for coins.
    * **2D Data Representation:** Managing a logical matrix of Countries x Coins.
* **Memory Management:**
    * Manual allocation and deallocation of memory for country names (`char*`).
* **File I/O:**
    * Custom file parsing using pipe `|` delimiters to handle multi-word country names safely.
* **Custom Utilities:**
    * Implementation of custom string functions (`strLen`, `strCopy`, `strCmp`) to manipulate raw C-strings.

## ⚙️ Build and Run

### Prerequisites
* C++ Compiler (GCC, Clang, MSVC).
* CMake (optional).

### Compilation
1.  Clone the repository:
    ```bash
    git clone [https://github.com/stefko681/euro-coin-collector.git](https://github.com/stefko681/euro-coin-collector.git)
    cd euro-coin-collector
    ```
2.  Build the project:
    ```bash
    cmake .
    make
    ```
3.  Run the application:
    ```bash
    ./Euro_coin_collector
    ```

## 📂 Data Storage

Data is stored in `coins.txt`. The format supports spaces in country names by using a specific delimiter.

**Format:**
```text
CountryName|c1 c2 c3 c4 c5 c6 c7 c8 Count
```
Example: ```text Germany|0 0 1 0 0 1 0 0 2```

## 👤 Author 

**Stefko Nikolaev**

* **Role: Software Engineering Student at FMI, Sofia University**
* **Focus: C++, Algorithms, and Data Structures**