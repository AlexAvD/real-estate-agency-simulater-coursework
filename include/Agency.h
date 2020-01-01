#pragma once

#include <iostream>
#include <vector>
#include "Date.h"
#include "Realtor.h"
#include "RealEstate.h"
#include "Client.h"

class Realtor;
class Agency {
  private:  
    int workDays_;
    int workHours_;
    double taxRate_;
    Date date_;
    std::stack<RealEstate> sold_;
    std::stack<RealEstate> rented_;
    std::vector<Realtor> realtors_;
    std::vector<Client> sellers_;
    std::vector<Client> buyers_;

  public:
    void simulateWorkMonth();
    void simulateWorkDay();

};