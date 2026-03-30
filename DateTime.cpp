#include "DateTime.hpp"
#include <iostream>
#include <iomanip>

int DateTime::operator-(const DateTime& other) {
    return getAbsoluteDays() - other.getAbsoluteDays();
}

DateTime DateTime::operator+(size_t days) {
    size_t absDays = getAbsoluteDays();
    return DateTime(absDays + days);
}

bool DateTime::operator==(const DateTime& other) const {
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}

bool DateTime::operator<(const DateTime& other) const {
    return getAbsoluteDays() < other.getAbsoluteDays();
    // if (year_ < other.year_) {
    //     return true;
    // }
    // if (year_ > other.year_) {
    //     return false;
    // }

    // if (month_ < other.month_) {
    //     return true;
    // }
    // if (month_ > other.month_) {
    //     return false;
    // }
    // return day_ < other.day_;
}

bool DateTime::operator<=(const DateTime& other) const {
    return ((*this) < other) || ((*this) == other);
}

bool DateTime::operator>(const DateTime& other) const {
    return !((*this) <= other);
}

bool DateTime::operator>=(const DateTime& other) const {
    return !((*this) < other);
}

bool DateTime::isLeap() const {
    if (year_ % 400 == 0) {
        return true;
    }
    return (year_ % 4 == 0) && (year_ % 100 != 0);
}


bool DateTime::isLeap(int year) const {
    if (year % 400 == 0) {
        return true;
    }
    return (year % 4 == 0) && (year % 100 != 0);

}


//returns 1 if today is Monday
//returns 7 if today is Sunday
size_t DateTime::getDayOfWeek() const {
    //actually in Gregorian calendar 01.01.1900 is Monday
    size_t absDays = getAbsoluteDays();
    // make +1 because of we want Monday = 1, not 0
    return absDays % 7 + 1;
}


size_t DateTime::getAmountDaysInMonth(int month) const {
    size_t nonLeapDays[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    size_t leapDays[12] {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeap()) {
        return leapDays[month-1];
    }
    return nonLeapDays[month-1];
}
 

//amount days since 01.01.1900
size_t DateTime::getAbsoluteDays() const {
    int deltaYears = year_ - 1900;
    int result = deltaYears * 365;
    int amountLeapYears = (deltaYears / 4) - (deltaYears / 100) + (deltaYears / 400);
    result += amountLeapYears;
    
    for (size_t i = 1; i < month_; ++i) {
        result += getAmountDaysInMonth(i);
    }
    result += day_;
    return result;
}
    
size_t DateTime::getYear() const {
    return year_;
}

size_t DateTime::getMonth() const {
    return month_;
}
    
size_t DateTime::getDay() const {
    return day_;
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
    os << std::setfill('0') << std::setw(4) << dt.getYear();
    os << "-" << std::setfill('0') << std::setw(2) << dt.getMonth();
    os << "-" << std::setfill('0') << std::setw(2) << dt.getDay();
    return os;
}

    
