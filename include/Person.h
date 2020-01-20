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
    // вектор с доступными именами для генерации случайного имени
    static const std::vector<std::vector<std::string>> names_;
    // вектор с доступными фамилиями для генерации случайного имени
    static const std::vector<std::vector<std::string>> surnames_;
    // вектор с доступными отчествами для генерации случайного имени
    static const std::vector<std::vector<std::string>> midnames_;

    // имя 
    std::string name_;
    // фамилия
    std::string surname_;
    // отчество
    std::string midname_;
    // паспортные данных: серия, номер
    std::string passportData_;
    // пол 
    bool gender_;
    // возраст
    int age_;

  public:
    Person();
    Person(const Person & person);
    ~Person();

    // генерирует случайное имя на основе параметра "gender" пол
    static std::string getRandomName(bool gender = 1);
    // генерирует случайную фамилию на основе параметра "gender" пол
    static std::string getRandomSurname(bool gender = 1);
    // генерирует случайное отчество на основе параметра "gender" пол
    static std::string getRandomMidname(bool gender = 1);

    // setters

    // устанавливает имя
    void setName(const std::string & name);
    // устанавливает фамилию 
    void setSurname(const std::string & surname);
    // устанавливает отчество
    void setMidname(const std::string & midname);
    // устанавливает фамилию имя отчество
    void setFullName(const std::string & fullName);
    // устанавливает паспортные данные
    void setPassportData(const std::string & passportData);
    // устанавливает пол
    void setGender(bool gender);
    // устанавливает пол 
    void setGender(const std::string &gender);
    // устанавливает возраст
    void setAge(int age);
    // устанавливает случайные свойства
    void setRandomProperties(int gender = -1);
    // принимает карту хранящую ключи, характеризующие свойства класса "Person", и их значения
    // и возвращает карту в которой хранятся ключи, к которым не было найдено подходящее свойство 
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &properties);

    // getters

    // возвращает имя
    std::string getName() const;
    // возвращает фамилию 
    std::string getSurname() const;
    // возвращает отчество
    std::string getMidname() const;
    // возвращает ФИО
    std::string getFullName() const;
    // возвращает паспортные данные
    std::string getPassportData() const;
    // возвращает пол
    bool getGender() const;
    // возвращает возраст
    int getAge() const;

    // others

    // функции для печати
    virtual std::ostream& print(std::ostream &out) const;
    friend std::ostream& operator<<(std::ostream &out, const Person &person);
};
