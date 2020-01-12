#include "Agency.h"

Agency::Agency() {
  workDays_ = 30;
  workHours_ = 12;
  taxRate_ = 0.15;
  chanceBuyerWillContact_ = 5;
  chanceSellerWillContact_ = 10;
  revenue_ = 0;
  saleCommision_ = 0.06;
  rentCommision_ = 0.5;
  salaryRate_ = 0.6;
  date_ = Date(); 
}

Agency::Agency(
  std::stack<Realtor> *realtors, 
  std::stack<Flat> *flats, 
  std::stack<House> *houses
) : Agency() {
  setRealtors(realtors);
  setFlats(flats);
  setHouses(houses);
  setClients();
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

void Agency::setClients() {
  Client *buyer;

  for (Flat &flat : flats_) {
    buyer = addClient(Client::generate());
    buyer->setRealEstate(&flat);  
  }

  for (House &house : houses_) {
    buyer = addClient(Client::generate());
    buyer->setRealEstate(&house);
  }

  shuffleVector(&clients_);
}

void Agency::setAvailableSellers() {
  for (Client &client : clients_) {
    addAvailableSeller(&client);
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

std::vector<Client> &Agency::getClients() {
  return clients_;
}

std::stack<Client*> &Agency::getBuyers() {
  return buyers_;
}

std::stack<Client*> &Agency::getSellers() {
  return sellers_;
}

std::stack<Client*> &Agency::getAvailableSellers() {
  return availableSellers_;
}

Client *Agency::getAvailableSeller() {
  Client *availableSeller = nullptr;

  if (!availableSellers_.empty()) {
    availableSeller = availableSellers_.top();

    availableSellers_.pop();
  }

  return availableSeller;
}

Client *Agency::getSeller() {
  Client *seller = nullptr;

  if (!sellers_.empty()) {
    seller = sellers_.top();

    sellers_.pop();
  }

  return seller;
}

Client *Agency::getBuyer() {
  Client *buyer = nullptr;

  if (!buyers_.empty()) {
    buyer = buyers_.top();

    buyers_.pop();
  }

  return buyer;
}

// others

Client *Agency::addSeller(Client *seller) {
  sellers_.push(seller);

  return sellers_.top();
}

Client *Agency::addBuyer(Client *buyer) {
  buyers_.push(buyer);

  return buyers_.top();
}

Client *Agency::addClient(const Client &client) {
  clients_.push_back(client);

  return &clients_.back();
}

Flat *Agency::addFlat(const Flat &flat) {
  flats_.push_back(flat);

  return &flats_.back();
}

House *Agency::addHouse(const House &house) {
  houses_.push_back(house);

  return &houses_.back();
}

Client *Agency::addAvailableSeller(Client *availableSeller) {
  availableSellers_.push(availableSeller);

  return availableSellers_.top();
}

Client *Agency::generateBuyer() {
  return addClient(Client::generate());
}

Client *Agency::generateSeller() {
  Client *buyer = generateBuyer();
  RealEstate *realEstate;
  
  if (chance(70)) {
    realEstate = addFlat(Flat::generate());
  } else {
    realEstate = addHouse(House::generate());
  }

  buyer->setRealEstate(realEstate);

  return buyer;
}

void Agency::generateAndAddBuyer() {
  addBuyer(generateBuyer());
}

void Agency::generateAndAddSeller() {
  addSeller(generateSeller());
}

void Agency::generateAndAddClient() {
  if (chance(chanceBuyerWillContact_)) {
    generateAndAddBuyer();
  }

  if (chance(chanceSellerWillContact_)) {
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
