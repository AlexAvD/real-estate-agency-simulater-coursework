#pragma once

#include <iostream>
#include <string>
#include <stack>

namespace coursework {
  
  class Person {
    private:
      std::string m_name;
      std::string m_surname;
      std::string m_gender;
      size_t m_age;

    public:
      Person();
      Person(std::string name, std::string surname, size_t age);

      void setName(std::string name);
      void setSurname(std::string surname);
      void setGender(std::string gender);
      void setAge(size_t age);

      void getName() const;
      void getSurname() const;
      void getGender() const;
      void getAge() const;

  };

  class Realtor: public Person {
    public:
      Realtor(std::string name, std::string surname, size_t age);
  };

  class Client: public Person {
    private:
      double m_balance;

    public:
      double getBalance() const;
  };

  // класс недвижимость
  class Property {
    private:
      // тип недвижимости, 0 - частный дом, 1 - квартира
      size_t m_type;
      size_t m_numOfRooms;
      double m_price;
  };

  // класс недвижимость на продажу
  class PropertySale : public Property {
    
  };

  // класс недвижимость на аренду
  class PropertyRent : public Property {

  };

  class Company {
    private:
      size_t m_workDays;
      size_t m_numOfPropertiesSold;
      size_t m_numOfPropertiesRent;
      float m_taxRate;
      std::string m_pathToRealtors;
      std::string m_pathToProperties;
      std::stack<Realtor> m_realtors;
      std::stack<Property> m_properties;

    public:
      Company(std::string pathToRealtors, std::string pathToProperties, size_t workDays);

      void setRealtors();
      void setProperties();
      Realtor & getRealtor();
      Property & getProperty();
      void simulation();
  };

}