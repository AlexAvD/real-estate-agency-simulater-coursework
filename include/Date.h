#pragma once

#include <iostream>
#include <string>
#include <cstdlib> 
#include <sstream>
#include <ctime>

class Date {
  private:
    static const short days_[13];
    static const std::time_t time_;
    static const std::tm* now_;

    short day_;
    short month_;
    short year_;

  public:
    Date();
    Date(short day, short month, short year);
    Date(const std::string date);
    Date(const Date& date);

    // setters
    void setDay(short day);
    void setMonth(short month);
    void setYear(short year);
    void setDate(short day, short month, short year);
  
    // getters
    short getDay() const;
    short getMonth() const;
    short getYear() const;
    std::string getDate() const;

    Date &operator++();
    Date &operator--();

    friend std::ostream& operator<<(std::ostream& out, const Date& date);
};