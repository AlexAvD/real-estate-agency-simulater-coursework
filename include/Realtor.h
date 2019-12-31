#pragma once

#include <stack>
#include "Person.h"
#include "Buyer.h"
#include "Seller.h"

class Realtor : Person {
  private:
    short experience_;
    Buyer* currentBuyer_;
    Seller* currentSeller_;
    std::stack<Buyer*> buyers_;
    std::stack<Seller*> sellers_;

  public: 
    Realtor();

    void addBuyer(Buyer* buyer);
    void addSeller(Buyer* buyer);
    Buyer* findBuyer();
    Seller* findSeller();
    void work();

    // setters
    void setExperience(short experience);
    void setWorkHours(short workHours);
    void setCurrentBuyer(Buyer* buyer);
    void setCurrentSeller(Seller* seller);
 
    // getters
    short getExperience() const;
    short getWorkHours() const;
    Buyer* getCurrentBuyer() const;
    Seller* getCurrentSeller() const;

    
};