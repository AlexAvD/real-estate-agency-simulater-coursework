#include "Realtor.h"

Realtor::Realtor() : Person() {
  experience_ = 0;
  charisma_ = 0.5;
  buyer_ = nullptr;
  realEstate_ = nullptr;
  agency_ = nullptr;
  date_ = Date();
}

Realtor::Realtor(Agency *agency) : Realtor() {
  agency_ = agency;
}

Realtor::Realtor(const Realtor &realtor) : Person(realtor) {  
  experience_ = realtor.experience_;
  charisma_ = realtor.charisma_;
  date_ = realtor.date_;
  reports_ = realtor.reports_;
  buyer_ = realtor.buyer_;
  agency_ = realtor.agency_;
  realEstate_ = realtor.realEstate_;
}

Realtor Realtor::generate() {
  Realtor realtor;

  realtor.setRandomProperties();

  return realtor;
}

void Realtor::getRealtorsFromFile(const std::string &pathToFile, std::stack<Realtor> *dist) {
	std::vector<std::map<std::string, std::string>> data = handleFile(pathToFile, ':');
	std::map<std::string, std::string> remainingProperties;
	
	for (auto &dataItem : data) {
    Realtor realtor;

    remainingProperties = realtor.setProperties(dataItem);

    if (remainingProperties.size()) {
      for (const auto &[key, val] : remainingProperties) {
        std::cerr << colorred << "Поля \"" << key << "\" не существует\n" << endcolor;
		  }
    }

		dist->push(realtor);
	}
}

// setters

void Realtor::setExperience(int experience) {
  experience_ = experience;
}

void Realtor::setCharisma(float charisma) {
  charisma_ = charisma;
}

void Realtor::setDate(const Date &date) {
  date_ = date;
}


void Realtor::setAgency(Agency *agency) {
  agency_ = agency;
}

void Realtor::setRealEstate(RealEstate *realEstate) {
  realEstate_ = realEstate;
}

void Realtor::setBuyer(Client *buyer) {
  buyer_ = buyer;
}

std::map<std::string, std::string> 
Realtor::setProperties(const std::map<std::string, std::string> &proprerties) {
  std::map<std::string, std::string> remainingProperties;

  for (const auto &[key, val] : Realtor::Person::setProperties(proprerties)) {
    if (key == "Опыт") {
      setExperience(std::stoi(val));
    } else if (key == "Харизма") {
      setCharisma(std::stof(val));
    } else {
      remainingProperties[key] = val;
    }
  }

  return remainingProperties;
}

void Realtor::setRandomProperties() {
  Realtor::Person::setRandomProperties();

  setExperience(Random::getInt(0, (getAge() - 25)));
  setCharisma(Random::getInt(20 + getExperience() * 2, 90) / 100.);
}


// getters

int Realtor::getExperience() const {
  return experience_;
}

float Realtor::getCharisma() const {
  return charisma_;
}

Date Realtor::getDate() const {
  return date_;
}

RealEstate *Realtor::getRealEstate() const {
  return realEstate_;
}

Client *Realtor::getBuyer() const {
  return buyer_;
}

std::vector<Report> Realtor::getReports() const {
  return reports_;
}


// others

void Realtor::addReport(
  const Date &date, RealEstate *realEstate, Client *buyer, long revenue
){
  reports_.push_back(Report(date, realEstate, buyer, revenue));
}
 

void Realtor::work() {
  if (!buyer_) {
    int chanceToFind = asymp(experience_, 1, 5, 2);

    if (chance(chanceToFind)) {
      Client *buyer = agency_->addBuyer(Client::generate());

      buyer_ = buyer;

      int days = 30 - asymp(charisma_, experience_, 30, 0.5) 
      + ((realEstate_->getSaleType() == 0) ? 5 : 0);

      date_.addDays(days);
    }

  } else {
    long revenue;
    long price = realEstate_->getPrice();
    int saleType = realEstate_->getSaleType();
    
    if (saleType == 0) {
      revenue = price * agency_->getSaleCommision();
    } else if (saleType == 1) {
      revenue = price * agency_->getRentCommision();
    }

    buyer_->setRealEstate(realEstate_);
    realEstate_->setOwner(buyer_);
    agency_->addSoldRealEstate(realEstate_);
    agency_->addRevenue(revenue);

    date_.setMinute(Random::getInt(0, 59));

    // std::cout << Report(date_, realEstate_, buyer_, revenue) << '\n';

    addReport(date_, realEstate_, buyer_, revenue);

    buyer_ = nullptr;
    realEstate_ = nullptr;
  }
}

std::ostream& Realtor::print(std::ostream &out) const {
  Realtor::Person::print(out);

  out 
    << "Опыт: " << experience_ 
    << '\n'
    << "Харизма: " << charisma_;

  return out;
}