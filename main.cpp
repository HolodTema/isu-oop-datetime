#include <iostream>
#include <fstream>
#include <vector>
#include "quickSort.hpp"
#include "DateTime.hpp"

void testDateTime() {
    std::cout << "Test DateTime class\n\n";

    DateTime dt1;
    std::cout << "Default constructor: " << dt1 << "\n\n";

    DateTime dt2(2024, 3, 15);
    std::cout << "Date-only constructor (2024-03-15): " << dt2 << "\n\n";

    DateTime dt3(2024, 12, 31, 23, 59, 59);
    std::cout << "Full constructor (2024-12-31T23:59:59): " << dt3 << "\n\n";

    DateTime dt4(0);
    std::cout << "Seconds constructor (0 seconds is 1900-01-01T00:00:00): " << dt4 << "\n\n";

    DateTime dt5(86400);
    std::cout << "Seconds constructor (86400 seconds is 1900-01-02T00:00:00): " << dt5 << "\n\n";

    std::cout << "Check InvalidDateException:\n";
    try {
        DateTime dateInvalid(2024, 2, 30);
        std::cout << "no exception\n";
    } catch (const InvalidDateException& e) {
        std::cout << e.what() << "\n";
    }
    std::cout << "\n";

    DateTime dt2024(2024, 1, 1);
    std::cout << "isLeapYear(2024): " << (dt2024.isLeapYear() ? "true" : "false") << "\n\n";

    DateTime dt2000(2000,1,1);
    std::cout << "isLeapYear(2000): " << (dt2000.isLeapYear() ? "true" : "false") << "\n\n";

    DateTime dt1900(1900,1,1);
    std::cout << "isLeapYear(1900): " << (dt1900.isLeapYear() ? "true" : "false") << "\n\n";

    DateTime dtFeb2024(2024,2,1);
    std::cout << "Days in February 2024: " << dtFeb2024.getAmountDaysInMonth(2) << "\n\n";

    DateTime dtFeb2023(2023,2,1);
    std::cout << "Days in February 2023: " << dtFeb2023.getAmountDaysInMonth(2) << "\n\n";

    DateTime dtMonday(2026,5,9);
    std::cout << "2026-05-09 must be Saturday: " << dtMonday.getDayOfWeek() << "\n\n";
    DateTime dtSunday(1900,1,7);
    std::cout << "1900-01-07 must be Sunday: " << dtSunday.getDayOfWeek() << "\n\n";

    std::cout << "Test operator + \n";
    DateTime dtDecember31(2024,12,31);
    DateTime dtJanuary01 = dtDecember31 + 1;
    std::cout << "2024-12-31 + 1 day = " << dtJanuary01 << "\n\n";

    std::cout << "Test operator - \n";
    int diffDays = dtJanuary01 - dtDecember31;
    std::cout << "Difference (2025-01-01 - 2024-12-31) in days: " << diffDays << "\n\n";

    DateTime dateA(2024,6,1);
    DateTime dateB(2024,6,2);
    std::cout << "Test compare-operators:\n";
    std::cout << "date a = " << dateA << "\n";
    std::cout << "date b = " << dateB << "\n";
    std::cout << "a < b: " << (dateA < dateB ? "true" : "false") << "\n";
    std::cout << "a > b: " << (dateA > dateB ? "true" : "false") << "\n";
    std::cout << "a == b: " << (dateA == dateB ? "true" : "false") << "\n";
    std::cout << "a <= b: " << (dateA <= dateB ? "true" : "false") << "\n";
    std::cout << "b >= a: " << (dateB >= dateA ? "true" : "false") << "\n";
}

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
    testDateTime();

    // sortDatesFromFile();

    // calculateCatholicPasha(2026);
    return 0;
}
