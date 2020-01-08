#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "Date.h"
#include "Seller.h"
#include "Buyer.h"

class Seller;
class Report {
  private:
    Seller *seller_;
    Buyer *buyer_;
    std::vector<std::pair<Date, std::string>> history_;

  public:
    Report();

    // setters

    void setSeller(Seller *seller);
    void setBuyer(Buyer *buyer);

    // getters

    Seller getSeller() const;
    Buyer getBuyer() const;
    std::vector<std::pair<Date, std::string>> getHistory() const;

    // others

    void addToHistory(const Date &date, const std::string &action);


    


};