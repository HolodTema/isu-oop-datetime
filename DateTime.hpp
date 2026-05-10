#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

#include <stdexcept>
#include <iosfwd>
#include <string>
#include "exceptions.hpp"

class DateTime {
public:
    static constexpr size_t START_YEAR = 1900;
    static constexpr size_t START_MONTH = 1;
    static constexpr size_t START_DAY = 1;
    static constexpr size_t START_HOUR = 0;
    static constexpr size_t START_MINUTE = 0;
    static constexpr size_t START_SECOND = 0;

    DateTime(
        size_t year,
        size_t month,
        size_t day,
        size_t hour,
        size_t minute,
        size_t second
    ):
        year_(year),
        month_(month),
        day_(day),
        hour_(hour),
        minute_(minute),
        second_(second)
    {
        if (!isValid()) {
            throw InvalidDateException();
        }
    }

    DateTime(
        size_t year,
        size_t month,
        size_t day
    ):
        year_(year),
        month_(month),
        day_(day),
        hour_(START_HOUR),
        minute_(START_MINUTE),
        second_(START_SECOND)
    {
        if (!isValid()) {
            throw InvalidDateException();
        }
    }

    DateTime():
        year_(START_YEAR),
        month_(START_MONTH),
        day_(START_DAY),
        hour_(START_HOUR),
        minute_(START_MINUTE),
        second_(START_SECOND)
    {
        if (!isValid()) {
            throw InvalidDateException();
        }
    }
    
    //days since 1900-01-01
    DateTime(size_t secondsSinceStart) {
        year_ = START_YEAR;

        while (true) {
            size_t secondsInYear = isLeapYear(year_) ? (366 * 86400) : (365 * 86400);
            if (secondsSinceStart < secondsInYear) {
                break;
            }
            secondsSinceStart -= secondsInYear;
            year_++;
        }

        month_ = START_MONTH;
        for (size_t m = START_MONTH; m <= 12; m++) {
            size_t secondsInMonth = getAmountDaysInMonth(m) * 86400;
            if (secondsSinceStart < secondsInMonth) {
                break;
            }
            secondsSinceStart -= secondsInMonth;
            month_++;
        }

        day_ = START_DAY + secondsSinceStart / 86400;
        secondsSinceStart %= 86400;

        hour_ = secondsSinceStart / 3600;
        secondsSinceStart %= 3600;

        minute_ = secondsSinceStart / 60;
        secondsSinceStart %= 60;

        second_ = secondsSinceStart;
    }

    int operator-(const DateTime& other) const;
    
    DateTime operator+(size_t days) const;

    bool operator==(const DateTime& other) const;
    
    bool operator>(const DateTime& other) const;

    bool operator>=(const DateTime& other) const;

    bool operator<(const DateTime& other) const;

    bool operator<=(const DateTime& other) const;

    bool isLeapYear() const;

    bool isLeapYear(size_t year) const;

    size_t getDayOfWeekZeller() const;

    size_t getDayOfWeek() const;

    size_t getAmountDaysInMonth(size_t month) const;

    size_t getSecondsSinceStart() const;

    size_t getSecondsSinceStartOfTheDay() const;

    bool isValid() const;

    size_t getYear() const;

    size_t getMonth() const;
    
    size_t getDay() const;

    size_t getHour() const;
    
    size_t getMinute() const;

    size_t getSecond() const;

    friend std::istream& operator>>(std::istream& is, DateTime& dateTime);

private:
    size_t year_;
    size_t month_;
    size_t day_;
    size_t hour_;
    size_t minute_;
    size_t second_;
};

std::istream& operator>>(std::istream& is, DateTime& dt);

std::ostream& operator<<(std::ostream& os, const DateTime& dt);

#endif
