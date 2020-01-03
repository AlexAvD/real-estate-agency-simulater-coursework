#include "Realtor.h"

Realtor::Realtor() {
  experience_ = 0;
  charisma_ = 0.5;
  currentBuyer_ = nullptr;
  currentSeller_ = nullptr;
  agency_ = nullptr;
}

Realtor::Realtor(Agency *agency) {
  currentBuyer_ = nullptr;
  currentSeller_ = nullptr;
  agency_ = agency;
}

void Realtor::setBuyer(Buyer *buyer) {
  currentBuyer_ = buyer;
}

void Realtor::setSeller(Seller *seller) {
  currentSeller_ = seller;
}

/* Buyer* Realtor::searchBuyer() {
  int percent = asymp(experience_, 20, 40, 2);

  if (chance(percent)) {
    Seller seller = Seller::generate();
    agency_->addSeller(seller);

    return agency_->getLastAddedBuyer();
  }

  return nullptr;
}
 */
Seller* Realtor::searchSeller() {
  int percent = asymp(experience_, 20, 60, 2);

  if (chance(percent)) {
    Seller seller = Seller::generate();
    agency_->addSeller(seller);

    return agency_->getLastAddedSeller();
  }

  return nullptr;
}


void Realtor::work() {
  /* if (!currentSeller_) {
    Seller *seller = searchSeller();
    
    if (seller) {
      currentSeller_ = seller;


    }
  }

  if (!seller) {

  } */
}

int Realtor::getExperience() const {
  return experience_;
}

std::ostream& Realtor::print(std::ostream &out) const {
  Realtor::Person::print(out);

  out 
    << "Experience: " << experience_ 
    << '\n'
    << "Charisma: " << charisma_;

  return out;
}