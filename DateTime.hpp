#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

#include <string>
#include <stdexcept>
#include <iosfwd>

class DateTime {
private:
    size_t year_;
    size_t month_;
    size_t day_;
    
public:

    //format yyyy-mm-dd
    DateTime(const std::string& date) {
        year_ = std::stoi(date.substr(0, 4));
        month_ = std::stoi(date.substr(5, 2));
        day_ = std::stoi(date.substr(8, 2));
        
        if (year_ < 1900) {
            throw std::runtime_error("Year cannot be < 0");
        }
        if (month_ == 0 || month_ > 12) {
            throw std::runtime_error("Month must be in interval [1, 12]");
        }
        if (day_ == 0 || day_ > 31) {
            throw std::runtime_error("Day must be in interval [1, 31]");
        }

        int amountDaysInCurrMonth = getAmountDaysInMonth(month_);
        if (day_ > amountDaysInCurrMonth) {
            throw std::runtime_error("Invalid day for this month");
        }
    }
    
    //days since 01.01.0001
    DateTime(size_t absDays) {
        size_t counterYear = 1900;
        size_t days = absDays;
        while (absDays - days > 365) {
            if (isLeap(counterYear)) {
                days -= 366;
            }
            else {
                days -= 365;
            }
            counterYear++;
        }
        year_ = counterYear;
        
        size_t counterMonth = 1;
        while (days > getAmountDaysInMonth(counterMonth)) {
            days -= getAmountDaysInMonth(counterMonth);
            counterMonth++;
        }
        month_ = counterMonth;
        day_ = days;
    }

    int operator-(const DateTime& other);
    
    DateTime operator+(size_t days);

    bool operator==(const DateTime& other) const;
    
    bool operator>(const DateTime& other) const;

    bool operator>=(const DateTime& other) const;

    bool operator<(const DateTime& other) const;

    bool operator<=(const DateTime& other) const;

    bool isLeap() const;

    bool isLeap(int year) const;

    size_t getDayOfWeek() const;

    size_t getAmountDaysInMonth(int month) const;

    size_t getAbsoluteDays() const;

    size_t getYear() const;

    size_t getMonth() const;
    
    size_t getDay() const;
};

std::ostream& operator<<(std::ostream& os, const DateTime& dt);

#endif
