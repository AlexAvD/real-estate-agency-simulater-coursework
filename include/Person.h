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

  public:
    Person();
    Person(const Person & person);
    ~Person();

    static std::string getRandomName(bool gender = 1);
    static std::string getRandomSurname(bool gender = 1);
    static std::string getRandomMidname(bool gender = 1);

     // setters
    void setName(const std::string & name);
    void setSurname(const std::string & surname);
    void setMidname(const std::string & midname);
    void setFullName(const std::string & fullName);
    void setPassportData(const std::string & passportData);
    void setGender(bool gender);
    void setGender(const std::string &gender);
    void setAge(int age);
    void setRandomProperties(int gender = -1);
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &proprerties);

    // getters
    std::string getName() const;
    std::string getSurname() const;
    std::string getMidname() const;
    std::string getFullName() const;
    std::string getPassportData() const;
    bool getGender() const;
    int getAge() const;

    // others
  
    virtual std::ostream& print(std::ostream &out) const;
    friend std::ostream& operator<<(std::ostream &out, const Person &person);
};
