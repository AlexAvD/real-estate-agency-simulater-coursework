#pragma once

#include <stack>
#include "Person.h"
#include "Client.h"
#include "Agency.h"
#include "Buyer.h"
#include "Seller.h"
#include "Contract.h"

class Agency;
class Realtor : public Person {
  private:
    int experience_;
    float charisma_;
    Agency *agency_;
    Buyer *currentBuyer_;
    Seller *currentSeller_;
    Contract *currentContract_;
    std::stack<Seller*> sellers_;
    std::stack<Contract> contracts_;

  public: 
    Realtor();
    Realtor(Agency* agencry);
    Realtor(const Realtor &realtor);

    // setters
    void setExperience(int experience);
    void setBuyer(Buyer *buyer);
    void setSeller(Seller *seller);
 
    // getters
    int getExperience() const;
    Client* getCurrentBuyer() const;
    Client* getCurrentSeller() const;

    // others
    void addBuyer(Client *buyer);
    void addSeller(Client *seller);

    void work();
    void searchBuyer();
    void searchSeller();
    void concludeContract();
    
    virtual std::ostream& print(std::ostream &out) const override;
};