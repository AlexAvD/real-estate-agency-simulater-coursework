#pragma once

#include <iostream>

class Person {
  private:
    std::string name_;
    std::string surname_;
    std::string midname_;
    std::string gender_;
    short age_;
    int salary_;
    long money_;

  public:
    Person();

    Person(std::string name, std::string surname, std::string midname,
      std::string gender, short age, int salary, long money);

    Person(std::string fullName, std::string gender, 
      short age, int salary, long money);

     // setters
    void setName(const std::string name);
    void setSurname(const std::string surname);
    void setMidname(const std::string midname);
    void setFullName(const std::string fullName);
    void setGender(const std::string gender);
    void setAge(short age);
    void setSalary(int salary);
    void setMoney(long money);

    // getters
    std::string getName() const;
    std::string getSurname() const;
    std::string getMidname() const;
    std::string getFullName() const;
    std::string getGender() const;
    unsigned short getAge() const;
    unsigned int getSalary() const;
    unsigned long getMoney() const;

    virtual std::ostream& print(std::ostream &out) const;

    friend std::ostream& operator<<(std::ostream &out, const Person &person);
};
