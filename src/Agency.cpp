#include "Agency.h"

Agency::Agency() {
  workDays_ = 30;
  workHours_ = 12;
  taxRate_ = 0.15;
  chanceBuyerWillAppeal_ = 2;
  chanceSellerWillAppeal_ = 4;
  nSold_ = 0;
  nRented_ = 0;
  revenue_ = 0;
  saleCommision_ = 0.06;
  rentCommision_ = 0.5;
  realtorCommision_ = 0.6;
  date_ = Date("", "07:00:00"); 
}

Agency::Agency(
  std::stack<Realtor> *realtors, 
  std::stack<Flat> *flats, 
  std::stack<House> *houses
) : Agency() {
  setRealtors(realtors);
  setFlats(flats);
  setHouses(houses);
  setAvailableSellers();
}

// settesr

void Agency::setRealtors(std::stack<Realtor> *realtors) {
  while (!realtors->empty()) {
    Realtor &realtor = realtors->top();

    realtor.setAgency(this);

    realtors_.push_back(realtor);

    realtors->pop();
  }
}

void Agency::setFlats(std::stack<Flat> *flats) {
  while (!flats->empty()) {
    Flat &flat = flats->top();

    flats_.push_back(flat);

    flats->pop();
  }
}

void Agency::setHouses(std::stack<House> *houses) {
  while (!houses->empty()) {
    House &house = houses->top();

    houses_.push_back(house);

    houses->pop();
  }
}

void Agency::setAvailableSellers() {
  Client seller;

  for (auto &flat : flats_) {
    seller = Client::generate();

    seller.setRealEstate(&flat);  

    addAvailableSeller(seller);
  }

  for (auto &house : houses_) {
    seller = Client::generate();

    seller.setRealEstate(&house);  

    addAvailableSeller(seller);
  }


  shuffleVector(&availableSellers_);
}

// getters

float Agency::getSaleCommision() const {
  return saleCommision_;
}

float Agency::getRentCommision() const {
  return rentCommision_;
}

float Agency::getRealtorCommision() const {
  return realtorCommision_;
}

long Agency::getRevenue() const {
  return revenue_;
}

Date Agency::getDate() const {
  return date_;
}

std::list<Realtor> &Agency::getRealtors() {
  return realtors_;
}

std::list<Flat> &Agency::getFlats() {
  return flats_;
}

std::list<House> &Agency::getHouses() {
  return houses_;
}

std::stack<Client> &Agency::getAppealedBuyers() {
  return appealedBuyers_;
}

std::stack<Client> &Agency::getAppealedSellers() {
  return appealedSellers_;
}

std::vector<Client> &Agency::getAvailableSellers() {
  return availableSellers_;
}

Client Agency::getAvailableSeller() {
  Client availableSeller;

  if (!availableSellers_.empty()) {
    availableSeller = availableSellers_.back();

    availableSellers_.pop_back();
  }

  return availableSeller;
}

Client Agency::getAppealedSeller() {
  Client aSeller = appealedSellers_.top();

  appealedSellers_.pop();

  return aSeller;
}

Client Agency::getAppealedBuyer() {
  Client aBuyer = appealedBuyers_.top();;

  appealedBuyers_.pop();

  return aBuyer;
}

// others

bool Agency::hasAppeals() const {
  return (didBuyerAppeal() || didSellerAppeal());
}

bool Agency::didBuyerAppeal() const {
  return (appealedBuyers_.size()) ? true : false;
}

bool Agency::didSellerAppeal() const {
  return (appealedSellers_.size()) ? true : false;
}

void Agency::addAvailableSeller(const Client &availableSeller) {
  availableSellers_.push_back(availableSeller);
}

void Agency::addAppealedSeller(const Client &seller) {
  appealedSellers_.push(seller);
}

void Agency::addAppealedBuyer(const Client &buyer) {
  appealedBuyers_.push(buyer);
}

Client *Agency::addBuyersPurchased(const Client &buyerPurchased) {
  RealEstate *realEstate = buyerPurchased.getRealEstate();
  
  int saleType = realEstate->getSaleType();

  if (saleType == 0) {
    ++nSold_;
  } else if (saleType == 1) {
    ++nRented_;
  }

  float commision = 1;
  
  if (saleType == 0) {
    commision = saleCommision_;
  } else if (saleType == 1) {
    commision = rentCommision_;
  }

  revenue_ += realEstate->getPrice() * commision; 

  std::string realEstateType = realEstate->getType();

  if (popularRealEstates_.find(realEstateType) == popularRealEstates_.end()) {
    popularRealEstates_[realEstateType] = 1;
  } else {
    ++popularRealEstates_[realEstateType];
  }

  buyersPurchased_.push(buyerPurchased);

  return &buyersPurchased_.top();
}


Flat *Agency::addFlat(const Flat &flat) {
  Flat &f = flats_.emplace_back(flat);

  return &f;
}

House *Agency::addHouse(const House &house) {
  House &h = houses_.emplace_back(house);

  return &h;
}

Client Agency::generateBuyer() {
  return Client::generate();
}

Client Agency::generateSeller() {
  Client buyer = generateBuyer();
  RealEstate *realEstate;

  if (chance(70)) {
    realEstate = addFlat(Flat::generate());
  } else {
    realEstate = addHouse(House::generate());
  }

  buyer.setRealEstate(realEstate);

  return buyer;
}

void Agency::generateAndAddBuyer() {
  addAppealedBuyer(generateBuyer());
}

void Agency::generateAndAddSeller() {
  addAppealedSeller(generateSeller());
}

void Agency::generateAndAddClient() {
  if (chance(chanceBuyerWillAppeal_)) {
    generateAndAddBuyer();
  }

  if (chance(chanceSellerWillAppeal_)) {
    generateAndAddSeller();
  }
}

void Agency::simulate() {
  for (int day = 0; day < workDays_; day++) {
    date_.setTime("07:00:00");

    for (int hour = 0; hour < workHours_; hour++) { 
      generateAndAddClient();

      for (Realtor &realtor : realtors_) { 
        if (realtor.getDate() <= date_) {
          realtor.setDate(date_);
          realtor.work();
        }
      }
      
      date_.addHours(1);
    } 

    date_.addDays(1);
  }
}

void Agency::writeReport(const std::string pathToFile) {
  std::ofstream file(pathToFile);

  if (file.is_open()) {
    
    file 
        << "\n"
        << center("ОТЧЁТ ПО РИЭЛТОРСОКОЙ ДЕЯТЕЛЬНОСТИ С " + Date().getDate() + " ПО " + date_.getDate(), 70) 
        << "\n" << divider(70, "╼") << "\n";

    long revenueWithSalaries = revenue_;
    long earnings = 0;
    long salaries = 0;

    for (Realtor &realtor : realtors_) {
      earnings = realtor.getEearnings();
      revenueWithSalaries -= earnings;
      salaries += earnings;

      std::stringstream title;

      title
        << divider(5, "-", 0) 
        << " Отчет сотрудника " << realtor.getFullName() << " "
        << divider(5, "-", 0);


      file << "\n" << center(title.str(), 70) << "\n\n";

      for (std::string &log : realtor.getLogs()) {
        file << log;
      }

      file << "\n" << divider(70, "╼") << "\n";
    }


    std::string popularRealEstateType = "";
    int nPurchases = 0;

    for (const auto &[key, val] : popularRealEstates_) {
      if (val > nPurchases) {
        nPurchases = val;
        popularRealEstateType = key;
      }
    }

    long tax = revenue_ * taxRate_;

    file
      << center("ИТОГИ", 70) << "\n\n"
      << li << "Кол-во проданной недвижимости: " << nSold_ << "\n"
      << li << "Кол-во сданной в аренду недвижимости: " << nRented_ << "\n"
      << li << "Популярная недвижимость по итогам месяца: " << popularRealEstateType << "\n"
      << li << "Доходы фирмы без учета НДС и зарплат сотрудников: " << revenue_ << " руб.\n"
      << li << "НДС фирмы составил: " << tax << " руб.\n"
      << li << "Зарплаты сотрудников составили: " << revenueWithSalaries << " руб.\n"
      << li << "Итого доход фирмы: " << revenue_ - tax - revenueWithSalaries << " руб.\n";

    file.close();
  }
}
