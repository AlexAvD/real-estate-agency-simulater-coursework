#pragma once

#include <iostream>
#include "Client.h"
#include "RealEstate.h"

class Buyer : public Client {
  private:

  public:
    Buyer();
    Buyer(const Buyer &buyer);

    void setRandomProperties();

    static Buyer generate();

    virtual std::ostream& print(std::ostream &out) const override;

};