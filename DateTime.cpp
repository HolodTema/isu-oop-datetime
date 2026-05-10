#include "DateTime.hpp"
#include <iostream>
#include <iomanip>

int DateTime::operator-(const DateTime& other) const{
    int deltaSeconds = getSecondsSinceStart() - other.getSecondsSinceStart();
    deltaSeconds /= 86400;
    return deltaSeconds;
}

DateTime DateTime::operator+(size_t days) const {
    size_t secondsToAdd = days * 86400;
    size_t currentSeconds = getSecondsSinceStart();
    return DateTime(currentSeconds + secondsToAdd);
}

bool DateTime::operator==(const DateTime& other) const {
    return year_ == other.year_ &&
        month_ == other.month_ &&
        day_ == other.day_ &&
        hour_ == other.hour_ &&
        minute_ == other.minute_ &&
        second_ == other.second_;
}

bool DateTime::operator<(const DateTime& other) const {
    return getSecondsSinceStart() < other.getSecondsSinceStart();
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

bool DateTime::isLeapYear() const {
    if (year_ % 400 == 0) {
        return true;
    }
    return (year_ % 4 == 0) && (year_ % 100 != 0);
}

bool DateTime::isLeapYear(size_t year) const {
    if (year % 400 == 0) {
        return true;
    }
    return (year % 4 == 0) && (year % 100 != 0);
}

size_t DateTime::getDayOfWeekZeller() const {
    // используем формулу Зеллера для нахождения дня недели из даты
    // вернет 1 если понедельник
    // вернет 7 если воскресенье
    // и тд

    size_t month = month_;
    size_t year = year_;
    if (month_ < 3) {
        month += 12;
        year--;
    }

    size_t a = year / 100;
    size_t b = year / 400;
    int c = 2 - a + b;
    size_t e = static_cast<size_t>(365.25 * (year + 4716));
    size_t f = static_cast<size_t>(30.6001 * (month + 1));
    size_t result = (c + day_ + e + f) % 7;

    // сейчас понедельник = 5, а воскресенье = 4 - исправим это
    result = (result + 3) % 7;
    return (result == 0) ? 7 : result;
}

size_t DateTime::getDayOfWeek() const {
    // 01.01.1900 - понедельник
    size_t dayOfWeek = (getSecondsSinceStart() / 86400) % 7;
    dayOfWeek++;
    return dayOfWeek;
}

size_t DateTime::getAmountDaysInMonth(size_t month) const {
    size_t days[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear()) {
        return 29;
    }
    return days[month - 1];
}

//amount seconds since 01.01.1900
size_t DateTime::getSecondsSinceStart() const {
    size_t result = 0;
    for (size_t y = START_YEAR; y < year_; y++) {
        result += isLeapYear(y) ? (366 * 86400) : (365 * 86400);
    }
    for (size_t m = START_MONTH; m < month_; m++) {
        result += getAmountDaysInMonth(m) * 86400;
    }
    result += (day_ - 1) * 86400;
    result += getSecondsSinceStartOfTheDay();
    return result;
}

size_t DateTime::getSecondsSinceStartOfTheDay() const {
    return second_ + minute_ * 60 + hour_ * 3600;
}

bool DateTime::isValid() const {
    return year_ >= START_YEAR &&
        month_ >= START_MONTH &&
        month_ <= 12 &&
        day_ >= START_DAY &&
        day_ <= getAmountDaysInMonth(month_) &&
        hour_ < 24 &&
        minute_ < 60 &&
        second_ < 60;
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

size_t DateTime::getHour() const {
    return hour_;
}

size_t DateTime::getMinute() const {
    return minute_;
}

size_t DateTime::getSecond() const {
    return second_;
}


std::istream& operator>>(std::istream& is, DateTime& dateTime) {
    std::istream::sentry s(is);
    if (!s) {
        return is;
    }
    
    std::string line;
    std::getline(is, line);

    size_t year;
    size_t month;
    size_t day;
    size_t hour;
    size_t minute;
    size_t second;

    if (line.size() == 8 && line[2] == ':' && line[5] == ':') {
        try {
            hour = std::stoi(line.substr(0, 2));
            minute = std::stoi(line.substr(3, 2));
            second = std::stoi(line.substr(6, 2));
        }
        catch (std::invalid_argument& e) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        dateTime.year_ = dateTime.START_YEAR;
        dateTime.month_ = dateTime.START_MONTH;
        dateTime.day_ = dateTime.START_DAY;
        dateTime.hour_ = hour;
        dateTime.minute_ = minute;
        dateTime.second_ = second;
        if (!dateTime.isValid()) {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }
    if (line.size() == 10 && line[4] == '-' && line[7] == '-') {
        try {
            year = std::stoi(line.substr(0, 4));
            month = std::stoi(line.substr(5, 2));
            day = std::stoi(line.substr(8, 2));
        }
        catch (std::invalid_argument& e) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        dateTime.year_ = year;
        dateTime.month_ = month;
        dateTime.day_ = day;
        dateTime.hour_ = dateTime.START_HOUR;
        dateTime.minute_ = dateTime.START_MINUTE;
        dateTime.second_ = dateTime.START_SECOND;
        if (!dateTime.isValid()) {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }
    if (line.size() == 19 &&
        line[4] == '-' &&
        line[7] == '-' &&
        line[10] == 'T' &&
        line[13] == ':' &&
        line[16] == ':')
    {
        try {
            year = std::stoi(line.substr(0, 4));
            month = std::stoi(line.substr(5, 2));
            day = std::stoi(line.substr(8, 2));
            hour = std::stoi(line.substr(11, 2));
            minute = std::stoi(line.substr(14, 2));
            second = std::stoi(line.substr(17, 2));
        }
        catch (std::invalid_argument& e) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        dateTime.year_ = year;
        dateTime.month_ = month;
        dateTime.day_ = day;
        dateTime.hour_ = hour;
        dateTime.minute_ = minute;
        dateTime.second_ = second;
        if (!dateTime.isValid()) {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }
    is.setstate(std::ios_base::failbit);
    return is;
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
    std::ostream::sentry s(os);
    if (!s) {
        return os;
    }

    os << std::setfill('0') << std::setw(4) << dt.getYear();
    os << "-" << std::setfill('0') << std::setw(2) << dt.getMonth();
    os << "-" << std::setfill('0') << std::setw(2) << dt.getDay();
    os << "T" << std::setfill('0') << std::setw(2) << dt.getHour();
    os << ":" << std::setfill('0') << std::setw(2) << dt.getMinute();
    os << ":" << std::setfill('0') << std::setw(2) << dt.getSecond();
    return os;
}

    
