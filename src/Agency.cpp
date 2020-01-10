#include "Agency.h"

Agency::Agency() {
  flats_ = nullptr;
  houses_ = nullptr;
  workDays_ = 30;
  workHours_ = 12;
  taxRate_ = 0.15;
  revenue_ = 0;
  saleCommision_ = 0.06;
  rentCommision_ = 0.5;
  date_ = Date(); 
}

Agency::Agency(
  std::stack<Realtor> *realtors, 
  std::stack<Flat> *flats, 
  std::stack<House> *houses
) : Agency() {
  setRealtors(realtors);

  flats_ = flats;
  houses_ = houses;
}

// settesr

void Agency::setRealtors(std::stack<Realtor> *realtors) {
  while (!realtors->empty()) {
    Realtor realtor = realtors->top();

    realtor.setAgency(this);

    realtors_.push_back(realtor);

    realtors->pop();
  }
}

void Agency::setFlats(std::stack<Flat> *flats) {
  flats_ = flats;
}

void Agency::setHouses(std::stack<House> *houses) {
  houses_ = houses;
}

// getters

float Agency::getSaleCommision() const {
  return saleCommision_;
}

float Agency::getRentCommision() const {
  return rentCommision_;
}

long Agency::getRevenue() const {
  return revenue_;
}

std::vector<Realtor> *Agency::getRealtors() {
  return &realtors_;
}

std::stack<Flat> *Agency::getFlats() {
  return flats_;
}

std::stack<House> *Agency::getHouses() {
  return houses_;
}

std::stack<Client> *Agency::getBuyers() {
  return &buyers_;
}

Date Agency::getDate() const {
  return date_;
}

Flat Agency::getFlat() {
  if (!flats_->empty()) {
    Flat flat = flats_->top();

    flats_->pop();

    return flat;
  }

  return Flat::generate();
}

House Agency::getHouse() {
  if (!houses_->empty()) {
    House house = houses_->top();

    houses_->pop();

    return house;
  }

  return House::generate();
}

RealEstate *Agency::getRealEstate() {
  RealEstate *realEstate;

  if (chance(70)) {
    realEstate = addFlatForSale(getFlat());
  } else {
    realEstate = addHouseForSale(getHouse());
  }

  return realEstate;
}

std::vector<RealEstate*> *Agency::getSoldRealEstates() {
  return &soldRealEstates_;
}

std::stack<House> *Agency::getHousesForSale() {
  return &housesForSale_;
}

std::stack<Flat> *Agency::getFlatsForSale() {
  return &flatsForSale_;
}

// others

void Agency::simulate() {
  for (int day = 0; day < workDays_; day++) {
    date_.setTime("07:00:00");

    for (int hour = 0; hour < workHours_; hour++) {

      for (Realtor &realtor : realtors_) { 

        if (realtor.getRealEstate() == nullptr) {
          realtor.setRealEstate(getRealEstate());
        }

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
  std::ofstream out;

  out.open(pathToFile);

  if (out.is_open()) {
    out 
    << "              ОТЧЁТ ПО РИЭЛТОРСОКОЙ ДЕЯТЕЛЬНОСТИ ЗА " << date_ << '\n'
    << "╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼\n\n";
    for (Realtor &realtor : realtors_) {
      out 
        << "Сотрудник " << realtor.getFullName() << " выполнил следующий план за данный месяц:\n\n";
        
      for (auto &report : realtor.getReports()) {
        out << report;
      }

      out << "╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼\n\n";
    }
  }


}

void Agency::addRevenue(int revenue) {
  revenue_ += revenue;
}

Client *Agency::addBuyer(const Client &buyer) { 
  buyers_.push(buyer);

  return &buyers_.top();
}

Flat *Agency::addFlatForSale(const Flat &flat) {
  flatsForSale_.push(flat);

  return &flatsForSale_.top();
}

House *Agency::addHouseForSale(const House &house) {
  housesForSale_.push(house);

  return &housesForSale_.top();
}

void Agency::addSoldRealEstate(RealEstate *realEstate) {
  soldRealEstates_.push_back(realEstate);
}

