#include "Agency.h"

Agency::Agency() {
  workDays_ = 30;
  workHours_ = 12;
  taxRate_ = 0.15;
  chanceBuyerWillAppeal_ = 5;
  chanceSellerWillAppeal_ = 10;
  revenue_ = 0;
  saleCommision_ = 0.06;
  rentCommision_ = 0.5;
  salaryRate_ = 0.6;
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

  shuffleVector(&flats_);

  for (Flat &flat : flats_) {
    seller = Client::generate();

    seller.setRealEstate(&flat);  

    addAvailableSeller(seller);
  }

  shuffleVector(&houses_);

  for (House &house : houses_) {
    seller = Client::generate();

    seller.setRealEstate(&house);  

    addAvailableSeller(seller);
  }
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

Date Agency::getDate() const {
  return date_;
}

std::vector<Realtor> &Agency::getRealtors() {
  return realtors_;
}

std::vector<Flat> &Agency::getFlats() {
  return flats_;
}

std::vector<House> &Agency::getHouses() {
  return houses_;
}

std::stack<Client> &Agency::getAppealedBuyers() {
  return appealedBuyers_;
}

std::stack<Client> &Agency::getAppealedSellers() {
  return appealedSellers_;
}

std::stack<Client> &Agency::getAvailableSellers() {
  return availableSellers_;
}

Client Agency::getAvailableSeller() {
  Client availableSeller;

  if (!availableSellers_.empty()) {
    availableSeller = availableSellers_.top();

    availableSellers_.pop();
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
  availableSellers_.push(availableSeller);
}

void Agency::addAppealedSeller(const Client &seller) {
  appealedSellers_.push(seller);
}

void Agency::addAppealedBuyer(const Client &buyer) {
  appealedBuyers_.push(buyer);
}

Flat *Agency::addFlat(const Flat &flat) {
  flats_.push_back(flat);

  return &flats_.back();
}

House *Agency::addHouse(const House &house) {
  houses_.push_back(house);

  return &houses_.back();
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
  addAvailableSeller(generateSeller());
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
  std::ofstream out;

  out.open(pathToFile);

  if (out.is_open()) {
    int nSold = 0;
    int nRented = 0;
    int saleType;
    int realtorSalary = 0;
    int totalSalary = 0;
    int tax = 0;
    long revenue = 0;

    out << "\n                  ОТЧЁТ ПО РИЭЛТОРСОКОЙ ДЕЯТЕЛЬНОСТИ ЗА " << date_.getDate() << '\n'
        << divider(85, "╼") << "\n";

    for (Realtor &realtor : realtors_) {
      out << "Сотрудник " << realtor.getFullName() << " выполнил следующий план за данный месяц:\n\n";

      realtorSalary = 0;

      for (Report &report : realtor.getReports()) {
        revenue       += report.getRevenue();
        realtorSalary += report.getRevenue();

        saleType = report.getRealEstate()->getSaleType();

        if (saleType == 0) {
          ++nSold;
        } else if (saleType == 1) {
          ++nRented;
        }

        out << report;
      }

      if (realtorSalary == 0 ) {
        out << "Не удалось продать/сдать недвивижимость\n";

        realtorSalary = realtor.getSalary();
      } else {
        realtorSalary -= realtorSalary * salaryRate_;
      }
      
      totalSalary += realtorSalary;

      out << divider(85, "╼") << "\n"
          << "Заплата сотруника за данный месяц составила " << (realtorSalary) << " руб.\n\n"
          << divider(85, "╼") << "\n";
    }

    tax = revenue * taxRate_;
    
    out << "Итоги: \n\n" 
        << li << "Кол-во проданной недвижимости: " << nSold << "\n"
        << li << "Кол-во сданной в аренду недвижимости: " << nRented << "\n"
        << li << "Доходы фирмы: " << revenue << " руб.\n"
        << li << "НДС фирмы составил: " << tax << " руб.\n"
        << li << "Зарплата сотрудников составила: " << totalSalary << "\n"
        << li << "Доходы фирмы с учетом НДС и зарплаты сотрудников: " << (revenue - tax - totalSalary) << " руб.\n";
  }

}

void Agency::addRevenue(int revenue) {
  revenue_ += revenue;
}
