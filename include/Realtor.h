#pragma once

#include <stack>
#include "Person.h"
#include "Buyer.h"
#include "Seller.h"
#include "Agency.h"

class Agency;
class Realtor : public Person {
  private:
    int experience_;
    Agency * agency_;
    Client* buyer_;
    Client* seller_;
    std::stack<Client*> buyers_;
    std::stack<Client*> sellers_;

  public: 
    Realtor();
    Realtor(Agency* agencry);

    void addBuyer(Client* buyer);
    void addSeller(Client* seller);
    Client* searchClient();
    void work();

    // setters
    void setExperience(int experience);
    void setBuyer(Client* buyer);
    void setSeller(Client* seller);
 
    // getters
    int getExperience() const;
    int getWorkHours() const;
    Client* getCurrentBuyer() const;
    Client* getCurrentSeller() const;

    
};