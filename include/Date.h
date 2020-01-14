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
    int hour_;
    int minute_;
    int second_;

  public:
    Date();
    Date(int day, int month, int year, int hour = 12, int minute = 0, int second = 0);
    Date(const std::string & date, const std::string & time = "12:00:00");
    Date(const Date& date);

    // setters

    Date &setDay(int day);
    Date &setMonth(int month);
    Date &setYear(int year);
    Date &setHour(int hour);
    Date &setMinute(int minute);
    Date &setSecond(int second);
    Date &setDate(int day, int month, int year);
    Date &setTime(int hour, int minute, int second);
    Date &setDate(const std::string &date);
    Date &setTime(const std::string &time);

    // getters

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getDateAndTime() const;

    // other

    Date &addMonths(int months);
    Date &addYears(int years);
    Date &addDays(int days);
    Date &addHours(int hours);
    Date &addMinutes(int minutes);
    Date &addSeconds(int seconds);

    // operators

    friend bool operator<(const Date &lhs, const Date &rhs);
    friend bool operator<=(const Date &lhs, const Date &rhs);
    friend bool operator>(const Date &lhs, const Date &rhs);
    friend bool operator>=(const Date &lhs, const Date &rhs);
    friend bool operator==(const Date &lhs, const Date &rhs);
    
    // output

    friend std::ostream& operator<<(std::ostream& out, const Date& date);
};