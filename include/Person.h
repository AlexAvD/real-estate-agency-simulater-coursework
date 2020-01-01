#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "helpers.h"
#include "Random.h"

class Person {
  private:
    static const std::vector<std::vector<std::string>> names_;
    static const std::vector<std::vector<std::string>> surnames_;
    static const std::vector<std::vector<std::string>> midnames_;
    std::string name_;
    std::string surname_;
    std::string midname_;
    std::string passportData_;
    bool gender_;
    int age_;
    int salary_;
    long money_;

  public:
    Person();

    Person(std::string name, std::string surname, std::string midname, 
      bool gender, std::string passportData, int age, int salary, long money = 0);

    Person(std::string fullName, bool gender, std::string passportData, 
      int age, int salary, long money = 0);

    static Person generate();

     // setters
    void setName(const std::string & name);
    void setSurname(const std::string & surname);
    void setMidname(const std::string & midname);
    void setFullName(const std::string & fullName);
    void setPassportData(const std::string & passportData);
    void setGender(bool gender);
    void setAge(int age);
    void setSalary(int salary);
    void setMoney(long money);

    // getters
    std::string getName() const;
    std::string getSurname() const;
    std::string getMidname() const;
    std::string getFullName() const;
    std::string getPassportData() const;
    bool getGender() const;
    int getAge() const;
    int getSalary() const;
    long getMoney() const;

    virtual std::ostream& print(std::ostream &out) const;

    friend std::ostream& operator<<(std::ostream &out, const Person &person);
};
