#pragma once

#include <iostream>
#include "Client.h"
#include "RealEstate.h"

class Seller : public Client {
  private:

  public:
    Seller();
    Seller(const Seller &seller);

    void setRandomProperties();

    static Seller generate();

    virtual std::ostream& print(std::ostream &out) const override;

};