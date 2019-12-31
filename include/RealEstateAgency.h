#pragma once

#include <iostream>
#include <vector>
#include "Date.h"
#include "Realtor.h"

class RealEstateAgency {
  private:  
    short workDays_;
    short workHours_;
    short nSolded_;
    short nRented_;
    float taxRate_;
    Date currentDate_;
    std::vector<Realtor> realtors_;

  public:
    void simulateWorkMonth();
    void simulateWorkDay();

};