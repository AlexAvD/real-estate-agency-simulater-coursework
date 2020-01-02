#pragma once

#include "Person.h"
#include "Client.h"
#include "RealEstate.h"

class Seller : public Client {
  private:

  public:
    Seller();
    Seller(const Person &person);
    Seller(const Person &person, RealEstate *realEstate);

    static Seller generate();

    virtual std::ostream& print(std::ostream &out) const override;

};