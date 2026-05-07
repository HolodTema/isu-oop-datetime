#include <iostream>
#include <fstream>
#include <vector>
#include "quickSort.hpp"
#include "DateTime.hpp"

void sortDatesFromFile() {
    std::ifstream ifs("./dates.txt");

    if (!ifs.is_open()) {
        std::cout << "Error: unable to open file with dates.\n";
    }

    size_t amountDates = 0;
    ifs >> amountDates;

    std::vector<DateTime> vecDates;
    vecDates.reserve(amountDates);

    for (size_t i = 0; i < amountDates; i++) {
        DateTime dateTime;
        ifs >> dateTime;
        if (!ifs) {
            std::cout << "Error: invalid date format at line " << i << "\n";
            ifs.close();
            return;
        }
        vecDates.push_back(dateTime);
    }

    quickSort(vecDates);

    std::cout << "Sorted dates:\n";
    for (auto it = vecDates.begin(); it != vecDates.end(); ++it) {
        std::cout << (*it) << "\n";
    }
}

int main() {
    sortDatesFromFile();
    return 0;
}
