#include "Date.h"

const int Date::days_[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::time_t Date::time_ = std::time(0);
const std::tm* Date::now_ = std::localtime(&Date::time_);

Date::Date() {
  day_ = now_->tm_mday;
  month_ = now_->tm_mon + 1;
  year_ = now_->tm_year + 1900;
}

Date::Date(int day, int month, int year) {
  setDate(day, month, year);
}

Date::Date(const Date &date) {
  day_ = date.day_;
  month_ = date.month_;
  year_ = date.year_;
}

Date::Date(const std::string date) {
  std::vector<std::string> tokenizedDate = tokenize(date, '.');

  setDate(
    stoi(tokenizedDate[0]),
    stoi(tokenizedDate[1]),
    stoi(tokenizedDate[2])
  );
}

void Date::setDay(int day) {
  day_ = day;

  while (day_ > days_[month_]) {
    day_ -= days_[month_++];

    if (day_ == 0) {
      day_ = 1;
    }

    if (month_ > 12) {
      year_++;
      month_ = 1;
    }
  }
}

void Date::setMonth(int month) {
  if (month > 12) {
    month_ = 12;
  } else if (month < 1) {
    month_ = 1;
  } else {
    month_ = month;
  }

  setDay(day_);
}

void Date::setYear(int year) {
  if (year > 2100) {
    year_ = 2100;
  } else if (year < 1970) {
    year_ = 1970;
  } else {
    year_ = year;
  }
}

void Date::setDate(int day, int month, int year) {
  setMonth(month);
  setDay(day);
  setYear(year);
}

int Date::getDay() const {
  return day_;
}

int Date::getMonth() const {
  return month_;
}

int Date::getYear() const {
  return year_;
}

std::string Date::getDate() const {
  std::ostringstream date;

  date.fill('0');
  date << std::setw(2) << day_ << '.';
  date << std::setw(2) << month_ << '.';
  date << year_;

  return date.str();
}

Date& Date::operator++() {
  if (++day_ > days_[month_]) {
    if (++month_ > 12) {
      month_ = 1;
      ++year_;
    }

    day_ = 1;
  }

  return *this;
}

Date& Date::operator--() {
  if (--day_ < 1) {
    if (--month_ < 1) {
      month_ = 12;
      --year_;
    }

    day_ = days_[month_];
  }

  return *this;
}

Date Date::operator+(int days) {
  Date result(*this);

  result.setDay(result.getDay() + days);
  
  return result;
}

std::ostream& operator<<(std::ostream &out, const Date &date) {
  out << date.getDate();

  return out;
}