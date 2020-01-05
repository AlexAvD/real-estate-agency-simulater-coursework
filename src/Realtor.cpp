#include "Realtor.h"

Realtor::Realtor() {
  experience_ = 0;
  charisma_ = 0.5;
  currentBuyer_ = nullptr;
  currentSeller_ = nullptr;
  agency_ = nullptr;
}

Realtor::Realtor(Agency *agency) : Realtor() {
  agency_ = agency;
}

Realtor::Realtor(const Realtor &realtor) : Person(realtor) {  
  experience_ = realtor.experience_;
  charisma_ = realtor.charisma_;
  currentBuyer_ = realtor.currentBuyer_;
  currentSeller_ = realtor.currentSeller_;
  agency_ = realtor.agency_;
}

void Realtor::setBuyer(Buyer *buyer) {
  currentBuyer_ = buyer;
}

void Realtor::setSeller(Seller *seller) {
  currentSeller_ = seller;
}

/* Buyer* Realtor::searchBuyer() {
  int percent = asymp(experience_, 10, 40, 2);

  if (chance(percent)) {
    Seller seller = Seller::generate();
    agency_->addSeller(seller);

    return agency_->getLastAddedBuyer();
  }

  return nullptr;
}
 */
void Realtor::searchSeller() {
  if (!currentBuyer_) {
    int percent = asymp(experience_, 20, 60, 2);

    if (chance(percent)) {
      Seller seller = Seller::generate();
      agency_->addSeller(seller);
      currentSeller_ = agency_->getLastAddedSeller();
    }
  }
}

void Realtor::concludeContract() {
  
}

void Realtor::work() {
  searchSeller();
  concludeContract();
  

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
    << "Опыт: " << experience_ 
    << '\n'
    << "Харизма: " << charisma_;

  return out;
}