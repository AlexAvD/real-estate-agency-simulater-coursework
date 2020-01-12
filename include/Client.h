#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "RealEstate.h"

class RealEstate;
class Client : public Person {
  private: 
    RealEstate *realEstate_;

  public:
    Client();
    Client(const Client &client);
    ~Client();

    static Client generate();

    // setters

    void setRealEstate(RealEstate *realEstate);
    void setRandomProperties();

    // getters
    RealEstate *getRealEstate() const;

    // others

    

    virtual std::ostream &print(std::ostream &out) const override;
};