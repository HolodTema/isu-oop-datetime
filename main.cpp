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

void calculateCatholicPasha(size_t year) {
    if (year < DateTime::START_YEAR) {
        std::cout << "Error: year must be > than START YEAR = " << DateTime::START_YEAR << "\n";
        return;
    }

    // используется алгоритм Гаусса для вычисления католической Пасхи

    // Пасха зависит от фазы Луны, фазы Луны повторяются каждые 19 лет
    int a = year % 19;
    // Остатки от деления на 4 и 7 - части солнечного цикла
    int b = year % 4;
    int c = year % 7;
    // номер столетия (на 1 меньше века)
    int century = year / 100;
    // поправка, уточняющая дату полнолуния для Грегорианского календаря
    int p = (13 + 8 * century) / 25;
    // учет високосных годов на рубеже веков в Грегорианском календаре
    int q = century / 4;
    // М - эпакта, то есть возраст Лунного диска на 1 марта
    int M = (15 - p + century - q) % 30;
    // N - Поправка для дней недели, берется из солнечных циклов
    int N = (4 + century - q) % 7;

    // d - дата крайнего полнолуния перед пасхой как количество дней после 21 марта.
    int d = (19 * a + M) % 30;
    // число дней, которые надо прибавить к дате крайнего полнолуния, чтобы получить
    // ближайшее воскресенье
    int e = (2 * b + 4 * c + 6 * d + N) % 7;

    // Исключения из алгоритма Гаусса
    // Их сделали в Средние Века, чтобы католическая Пасха не совпадала с иудейской Пасхой.
    if (d == 29 && e == 6) {
        DateTime datePasha(year, 4, 19);
        std::cout << "Catholic Pasha = " << datePasha << "\n";
        return;
    }
    if (d == 28 && e == 6 && ((11 * M + 11) % 30) < 19) {
        DateTime datePasha(year, 4, 18);
        std::cout << "Catholic Pasha = " << datePasha << "\n";
        return;
    }

    // основной алгоритм Гаусса для вычисления Пасхи по созданным ранее коэффицентам
    if ((d + e) <= 9) {
        DateTime datePasha(year, 3, 22 + d + e);
        std::cout << "Catholic Pasha = " << datePasha << "\n";
    }
    else {
        DateTime datePasha(year, 4, d + e - 9);
        std::cout << "Catholic Pasha = " << datePasha << "\n";
    }
}

int main() {
    // sortDatesFromFile();

    calculateCatholicPasha(2026);
    return 0;
}
