#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "RealEstate.h"

class Client : public Person {
  private:
    // тип клиента: 
    // 0 - продавец, 1 - арендодатель, 
    // 2 - покупатель, 3 - арендатор
    int type_; 
    RealEstate *realEstate_;

  protected: 
    static const std::vector<std::string> types_;

  public:
    Client();
    Client(const Client &client);

    // setters
    void setType(int type = -1);
    void setRealEstate(RealEstate *realEstate);
    void setRandomProperties();

    // getters
    int getType() const;
    RealEstate *getRealEstate() const;

    virtual std::ostream &print(std::ostream &out) const override;
};