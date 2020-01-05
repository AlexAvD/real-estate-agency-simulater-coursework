#include "Date.h"

const int Date::days_[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::time_t Date::time_ = std::time(0);
const std::tm* Date::now_ = std::localtime(&Date::time_);

Date::Date() {
  day_ = now_->tm_mday;
  month_ = now_->tm_mon + 1;
  year_ = now_->tm_year + 1900;
  hour_ = now_->tm_hour;
  minute_ = now_->tm_min;
  second_ = now_->tm_sec;
}

Date::Date(int day, int month, int year, int hour, int minute, int second) {
  setDate(day, month, year);
  setTime(hour, minute, second);
}

Date::Date(const Date &date) {
  day_ = date.day_;
  month_ = date.month_;
  year_ = date.year_;
  hour_ = date.hour_;
  minute_ = date.minute_;
  second_ = date.second_;
}

Date::Date(const std::string & date, const std::string & time) {
  setDate(date);
  setTime(time);
}

void Date::setYear(int year) {
  if (year > 9999) {
    year_ = 9999;
  } else if (year < 0) {
    year_ = 0;
  } else {
    year_ = year;
  }
}

void Date::setMonth(int month) {
  if (month > 12 || month < 1) {
    month_ = (11 + month % 12 ) % 12 + 1;
  } else {
    month_ = month;
  }
}

void Date::setDay(int day) {
  if (day > days_[month_] || day < 1) {
    day_ = ((days_[month_] - 1) + day % days_[month_]) %  days_[month_] + 1;
  } else {
    day_ = day;
  }
}

void Date::setHour(int hour) {
  if (hour > 23) {
    hour_ %= 24;
  } else if (hour < 0) {
    hour_ = (24 + hour % 24) % 24;
  } else {
    hour_ = hour;
  }
}

void Date::setMinute(int minute) { 
  if (minute > 59) {
    minute_ %= 60;
  } else if (minute < 0) {
    minute_ = (60 + minute % 60) % 60;;
  } else {
    minute_ = minute;
  }
}

void Date::setSecond(int second) {
  if (second > 59) {
    second_ %= 60;
  } else if (second < 0) {
    second_ = (60 + second % 60) % 60;
  } else {
    second_ = second;
  }
}

void Date::setDate(int day, int month, int year) {
  setMonth(month);
  setDay(day);
  setYear(year);
}

void Date::setDate(const std::string &date) {
  std::vector<std::string> tokenizedDate = tokenize(date, '.');

  setDate(
    stoi(tokenizedDate[0]),
    stoi(tokenizedDate[1]),
    stoi(tokenizedDate[2])
  );
}

void Date::setTime(int hour, int minute, int second) {
  setHour(hour);
  setMinute(minute);
  setSecond(second);
}

void Date::setTime(const std::string & time) {
  std::vector<std::string> tokenizedTime = tokenize(time, ':');

  setTime(
    stoi(tokenizedTime[0]),
    stoi(tokenizedTime[1]),
    stoi(tokenizedTime[2])
  );
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

int Date::getHour() const {
  return hour_;
}

int Date::getMinute() const {
  return minute_;
}

int Date::getSecond() const {
  return second_;
}

std::string Date::getDate() const {
  std::ostringstream date;

  date.fill('0');

  date 
    << std::setw(2) << day_ << '.'
    << std::setw(2) << month_ << '.'
    << year_;

  return date.str();
}

std::string Date::getTime() const {
  std::ostringstream time;

  time.fill('0');

  time 
    << std::setw(2) << hour_ << ':'
    << std::setw(2) << minute_ << ':'
    << std::setw(2) << second_;

  return time.str();
}

std::string Date::getDateAndTime() const {
  return getDate() + ' ' + getTime();
}

Date &Date::addYears(int years) {
  setYear(year_ + years);

  return *this;
}

Date &Date::addMonths(int months) {
  int years, month;

  months = month_ + months;
  month = months % 12;
  years = months / 12;

  if (month < 1) {
    --years;
  }

  setMonth(month);
  setDay(day_);

  if (years) {
    addYears(years);
  }
  return *this;
}

Date &Date::addDays(int days) {
  int sign = getSign(days);

  do {
    day_ += sign;

    if (day_ > days_[month_]) {
      day_ = 1;
      addMonths(sign);
    } 

    if (day_ < 1) {
      addMonths(sign);
      day_ = days_[month_];
    }
  } while (days -= sign);

  return *this;
}

Date &Date::addHours(int hours) {
  int days, hour;

  hours = hour_ + hours;
  hour = hours % 24;
  days = hours / 24;

  if (hour < 0) {
    --days;
  }

  setHour(hour);

  if (days) {
    addDays(days);
  }

  return *this;
}

Date &Date::addMinutes(int minutes) {
  int hours, minute;

  minutes = minute_ + minutes;
  minute = minutes % 60;
  hours = minutes / 60;

  if (minute < 0) {
    --hours;
  }

  setMinute(minute);

  if (hours) {
    addHours(hours);
  }

  return *this;
}

Date &Date::addSeconds(int seconds) {
  int minutes, second;

  seconds = second_ + seconds;
  second = seconds % 60;
  minutes = seconds / 60;

  if (second < 0) {
    --minutes;
  }

  setSecond(second);

  if (minutes) {
    addMinutes(minutes);
  }

  return *this;
}

std::ostream& operator<<(std::ostream &out, const Date &date) {
  out << date.getDateAndTime();

  return out;
}