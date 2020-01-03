#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include "Date.h"
#include "Realtor.h"
#include "RealEstate.h"
#include "Client.h"
#include "Realtor.h"

class Buyer;
class Seller;
class Realtor;
class Agency {
  private:  
    int workDays_;
    int workHours_;
    long long money_;
    float taxRate_;
    Date date_;
    std::vector<Realtor> realtors_;
    std::vector<Seller> dbSellers_;
    std::stack<Seller> sellers_;
    std::stack<Buyer> buyers_;

  public:
    Agency();
    Agency(std::vector<Realtor> realtors, std::vector<Seller> sellers, 
      int workDays = 30, int workHours = 12, float taxRate = 0.15);

    Buyer* getLastAddedBuyer();
    Seller* getLastAddedSeller();
    Date getDate() const;
    
    void addSeller(Seller client);
    void addBuyer(Buyer buyer);

    void simulate();

    
};