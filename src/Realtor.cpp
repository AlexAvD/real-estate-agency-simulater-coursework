#include "Realtor.h"

Realtor::Realtor() : Person() {
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

Realtor Realtor::generate() {
  Realtor realtor;

  realtor.setRandomProperties();

  return realtor;
}

// setters

void Realtor::setExperience(int experience) {
  experience_ = experience;
}

void Realtor::setCharisma(float charisma) {
  charisma_ = charisma;
}

void Realtor::setCurrentBuyer(Buyer *buyer) {
  currentBuyer_ = buyer;
}

void Realtor::setCurrentSeller(Seller *seller) {
  currentSeller_ = seller;
}

// getters

int Realtor::getExperience() const {
  return experience_;
}

float Realtor::getCharisma() const {
  return charisma_;
}

Buyer *Realtor::getCurrentBuyer() const {
  return currentBuyer_;
}

Seller *Realtor::getCurrentSeller() const {
  return currentSeller_;
}

void Realtor::setRandomProperties() {
  Realtor::Person::setRandomProperties();

  setExperience(Random::getInt(0, 20));
  setCharisma(Random::getInt(30, 90) / 100.);
}


void Realtor::searchClient() {
  Buyer *buyer;
  Seller *seller;

  if (!currentClient_) {
    buyer = searchBuyer();
  } 
}

Buyer* Realtor::searchBuyer() {
  int percent = asymp(experience_, 10, 40, 2);

  if (chance(percent)) {
    Seller seller = Seller::generate();
    agency_->addSeller(seller);

    return agency_->getLastAddedBuyer();
  }

  return nullptr;
}

Seller *Realtor::searchSeller() {
  if (!currentSeller_) {
    int percent = asymp(experience_, 20, 60, 2);

    if (chance(percent)) {
      Seller seller = Seller::generate();
      agency_->addSeller(seller);
      currentSeller_ = agency_->getLastAddedSeller();
    }
  }

  return nullptr;
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

std::ostream& Realtor::print(std::ostream &out) const {
  Realtor::Person::print(out);

  out 
    << "Опыт: " << experience_ 
    << '\n'
    << "Харизма: " << charisma_;

  return out;
}