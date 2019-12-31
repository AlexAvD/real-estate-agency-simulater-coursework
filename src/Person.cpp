#include <sstream>
#include <vector>
#include <algorithm>
#include "helpers.h"
#include "Person.h"

Person::Person() {
  name_ = "";
  surname_ = "";
  midname_ = "";
  gender_ = "";
  age_ = 0;
  salary_ = 0;
  money_ = 0;
}

Person::Person(
  std::string name, std::string surname, std::string midname,
  std::string gender, short age, int salary, long money
) {
  setName(name);
  setSurname(surname);
  setMidname(midname);
  setGender(gender);
  setAge(age);
  setSalary(salary);
  setMoney(money);
}

Person::Person(
  std::string fullName, std::string gender, 
  short age, int salary, long money
) {
  setFullName(fullName);
  setGender(gender);
  setAge(age);
  setSalary(salary);
  setMoney(money);
}

// setters

void Person::setName(std::string name) {
  name_ = name;
}

void Person::setSurname(std::string surname) {
  surname_ = surname;
}

void Person::setMidname(std::string midname) {
  midname_ = midname;
}

void Person::setFullName(std::string fullName) {
  std::vector<std::string> tokens = tokenize(fullName, ' ');

  setName(tokens[0]);
  setSurname(tokens[1]);
  setMidname(tokens[2]);
}

void Person::setGender(std::string gender) {
  gender_ = gender;
}

void Person::setAge(short age) {
  age_ = age;
}

void Person::setSalary(int salary) {
  salary_ = salary;
}

void Person::setMoney(long money) {
  money_ = money;
}

// getters

std::string Person::getName() const {
  return name_;
}

std::string Person::getSurname() const {
  return surname_;
}

std::string Person::getMidname() const {
  return midname_;
}

std::string Person::getFullName() const {
  std::string fullName = name_ + ' ' + surname_ + ' ' + midname_;

  return fullName;
}

std::string Person::getGender() const {
  return gender_;
}

unsigned short Person::getAge() const {
  return age_;
}
 
unsigned int Person::getSalary() const {
  return salary_;
}

unsigned long Person::getMoney() const {
  return money_;
}

std::ostream& operator<<(std::ostream &out, const Person &person) {
  return person.print(out);
}

std::ostream& Person::print(std::ostream &out) const {
  out << "Full name: " << getFullName() << '\n'
      << "Gender: " << getGender() << '\n'
      << "Age: " << getAge() << '\n'
      << "Salary: " << getSalary() << " руб." << '\n'
      << "Money: " << getMoney() << " руб." << '\n';

  return out;
}
