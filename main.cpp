#include <iostream>
#include "DateTime.hpp"

int main() {
    DateTime dt1("2026-03-30");
    std::cout << "Days since 1900-01-01 to 2026-03-30: " << dt1.getAbsoluteDays() << "\n";

    DateTime dt2("2025-03-20");
    int deltaDays = dt1 - dt2;
    std::cout << "Delta between 2026-03-30 and 2025-03-20: " << deltaDays << "\n";
    
    return 0;
}
