#include "Report.h"

Report::Report() {
  buyer_ = nullptr;
  realEstate_ = nullptr;
  date_ = Date("0.0.0");
  revenue_ = 0;
}

// setters

Report::Report(
  const Date &date, 
  RealEstate *realEstate, Client *buyer, long revenue
) {
  date_ = date;
  realEstate_ = realEstate;
  buyer_ = buyer;
  revenue_ = revenue;
}

Report::Report(const Report &report) {
  date_ = report.date_;
  realEstate_ = report.realEstate_;
  buyer_ = report.buyer_;
  revenue_ = report.revenue_;
}

long Report::getRevenue() const {
  return revenue_;
}

RealEstate *Report::getRealEstate() const {
  return realEstate_;
}
