#include "Report.h"

Report::Report() {
  seller_ = nullptr;
  buyer_ = nullptr;
}

// setters

void Report::setSeller(Seller *seller) {
  seller_ = seller;
}

void Report::setBuyer(Buyer *buyer) { 
  buyer_ = buyer;
} 

// getters

Seller Report::getSeller() const {  
  return *seller_;
}

Buyer Report::getBuyer() const {
  return *buyer_;
}
  
std::vector<std::pair<Date, std::string>> Report::getHistory() const {
  return history_;
}
 
// others

void Report::addToHistory(const Date &date, const std::string &action) {
  std::pair<Date, std::string> historyItem({date, action}); 
  
  history_.push_back(historyItem); 
}
