#pragma once

#include <iostream>
#include "Person.h"
#include "RealEstate.h"

class Client : public Person {
  private:
    int type; // тип клиента: 0 - продавец, 1 - покупатель, 
    RealEstate * realEstate_;

  public:
    Client();
    /* Client(std::string name, std::string surname, std::string midname,
      std::string gender, int age, int salary, long money);

    Client(std::string fullName, std::string gender, 
      int age, int salary, long money); */


};