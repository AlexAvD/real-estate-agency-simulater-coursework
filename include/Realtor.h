#pragma once

#include <stack>
#include "Person.h"
#include "Client.h"
#include "Agency.h"
#include "Buyer.h"
#include "Seller.h"

class Agency;
class Realtor : public Person {
  private:
    int experience_;
    float charisma_;
    Agency *agency_;
    Buyer *currentBuyer_;
    Seller *currentSeller_;
    std::stack<Seller*> sellers_;

  public: 
    Realtor();
    Realtor(Agency* agencry);

    // setters
    void setExperience(int experience);
    void setBuyer(Buyer *buyer);
    void setSeller(Seller *seller);
 
    // getters
    int getExperience() const;
    Client* getCurrentBuyer() const;
    Client* getCurrentSeller() const;

    void addBuyer(Client *buyer);
    void addSeller(Client *seller);
    void work();
    Buyer* searchBuyer();
    Seller* searchSeller();
    
    virtual std::ostream& print(std::ostream &out) const override;
};