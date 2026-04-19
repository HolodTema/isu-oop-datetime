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
    size_t hour_;
    size_t minute_;
    size_t second_;
    
public:

    DateTime(const std::string& date) {
        if (date.size == 10 || date.size == 19) {
            //format yyyy-mm-ddThh:mm:ss
            //or format yyyy-mm-dd
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
            if (date.size == 19) {
                //format yyyy-mm-ddThh:mm:ss
                hour_ = std::stoi(date.substr(11, 2));
                minute_ = std::stoi(date.substr(14, 2));
                second_ = std::stoi(date.substr(17, 2));
                
                if (hour_ >= 24) {
                    throw std::runtime_error("Hour must be in interval [0, 23]");
                }
                if (minute_ >= 60) {
                    throw std::runtime_error("Minute must be in interval [0, 59]");
                }
                if (second_ >= 60) {
                    throw std::runtime_error("Second must be in interval [0, 59]");
                }
            }
            else {
                hour_ = 0;
                minute_ = 0;
                second_ = 0;
            }
        }
        else if (date.size == 8) {
            hour_ = std::stoi(date.substr(0, 2));
            minute_ = std::stoi(date.substr(3, 2));
            second_ = std::stoi(date.substr(6, 2));
            
            if (hour_ >= 24) {
                throw std::runtime_error("Hour must be in interval [0, 23]");
            }
            if (minute_ >= 60) {
                throw std::runtime_error("Minute must be in interval [0, 59]");
            }
            if (second_ >= 60) {
                throw std::runtime_error("Second must be in interval [0, 59]");
            }
        }
        else {
            throw std::runtime_error("Invalid date format");
        }
    }
    
    //days since 1900-01-01
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

    size_t getTimeSeconds() const;

    size_t getYear() const;

    size_t getMonth() const;
    
    size_t getDay() const;

    size_t getHour() const;
    
    size_t getMinute() const;

    size_t getSecond() const;
};

std::istream& operator>>(std::istream& is, DateTime& dt);

std::ostream& operator<<(std::ostream& os, const DateTime& dt);

#endif
