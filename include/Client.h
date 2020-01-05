#pragma once

#include <iostream>
#include "Person.h"
#include "RealEstate.h"

// class Seller;
class Client : public Person {
  protected:
    // int type; // тип клиента: 0 - продавец, 1 - покупатель, 
    RealEstate *realEstate_;

  public:
    Client();
    Client(const Person &person);
    Client(const Person &person, RealEstate *RealEstate);

    static Client generate();

    void setRealEstate(RealEstate *realEstate);

    RealEstate * getRealEstate() const;

    virtual std::ostream& print(std::ostream &out) const override;

};