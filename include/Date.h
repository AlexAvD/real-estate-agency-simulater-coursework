#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib> 
#include <sstream>
#include <ctime>
#include "helpers.h"

class Date {
  private:
    static const int days_[13];
    static const std::time_t time_;
    static const std::tm* now_;

    int day_;
    int month_;
    int year_;

  public:
    Date();
    Date(int day, int month, int year);
    Date(const std::string date);
    Date(const Date& date);

    // setters
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    void setDate(int day, int month, int year);
  
    // getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    std::string getDate() const;

    Date &operator++();
    Date &operator--();
    Date operator+(int days);

    friend std::ostream& operator<<(std::ostream& out, const Date& date);
};