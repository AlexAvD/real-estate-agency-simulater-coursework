#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "RealEstate.h"

class RealEstate;
class Client : public Person {
  private: 
    // недвижимость которой владеет клиент
    RealEstate *realEstate_;

  public:
    Client();
    Client(const Client &client);
    ~Client();

    // генерирует клиента со случайными свойствами
    static Client generate();

    // setters

    // устанавливает недвижимость
    void setRealEstate(RealEstate *realEstate);
    // устанавливает случайные свойства
    void setRandomProperties();

    // getters

    // возвращает недвижимость
    RealEstate *getRealEstate() const;

    // others

    virtual std::ostream &print(std::ostream &out) const override;
};