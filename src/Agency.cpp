#include "Agency.h"

Agency::Agency() {
  workDays_ = 30;
  workHours_ = 12;
  taxRate_ = 0.15;
  money_ = 10000000;
  date_ = Date();
  
}

Agency::Agency(
  std::vector<Realtor> realtors, std::vector<Seller> sellers, 
  int workDays, int workHours, float taxRate
) {
  realtors_ = realtors;
  dbSellers_ = sellers;
  workDays_ = workDays;
  workHours_ = workHours;
  taxRate_ = taxRate;
  money_ = 10000000;
  date_ = Date();
}

Buyer* Agency::getLastAddedBuyer() {
  return &buyers_.top();
}

Seller* Agency::getLastAddedSeller() {
  return &sellers_.top();
}

Date Agency::getDate() const {
  return date_;
}

void Agency::simulate() {
  for (int day = 0; day < workDays_; day++) {
    date_.setTime("07:00:00");

    for (int hour = 0; hour < workHours_; hour++) {
      date_.addHours(1);
      
      for (Realtor &realtor : realtors_) { 
        realtor.work();
      }
    } 

    date_.addDays(1);
  }
} 

void Agency::addSeller(Seller seller) {
  sellers_.push(seller);
}

void Agency::addBuyer(Buyer buyer) {
  sellers_.push(buyer);
}