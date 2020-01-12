#include "Realtor.h"

Realtor::Realtor() : Person() {
  experience_ = 0;
  charisma_ = 0.5;
  salary_ = 0;

  maxSellers_ = 3;
  chanceToConcludeContract_ = 70;

  contractConcluded_ = false;
  isSearching_ = false;
  allSellersFound_ = false;
  isViewing_ = false;

  buyer_ = nullptr;
  agency_ = nullptr;
  date_ = Date();
}

Realtor::Realtor(const Realtor &realtor) : Person(realtor) {  
  experience_ = realtor.experience_;
  charisma_ = realtor.charisma_;
  salary_ = realtor.salary_;
  maxSellers_ = realtor.maxSellers_;
  isSearching_ = realtor.isSearching_;
  date_ = realtor.date_;
  buyer_ = realtor.buyer_;
  agency_ = realtor.agency_;

  sellers_ = realtor.sellers_;
  reports_ = realtor.reports_;
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

void Realtor::setSalary(int salary) {
  salary_ = salary;
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
    } else if (key == "Зарплата") {
      setSalary(std::stof(val));
    } else {
      remainingProperties[key] = val;
    }
  }

  return remainingProperties;
}

void Realtor::setRandomProperties() {
  Realtor::Person::setRandomProperties();

  int minSalary = 25000;
  int maxSalary = 30000 + experience_ * 1000;

  setSalary(Random::getInt(minSalary, maxSalary));

  int minExperience = 0;
  int maxExperience = getAge() - 25;

  setExperience(Random::getInt(minExperience, maxExperience));

  int minCharisma = (20 + experience_) * 2;
  int maxCharisma = 90;

  setCharisma(Random::getInt(minCharisma, maxCharisma) / 100.);
}


// getters

int Realtor::getExperience() const {
  return experience_;
}

int Realtor::getSalary() const {
  return salary_;
}

float Realtor::getCharisma() const {
  return charisma_;
}

Date Realtor::getDate() const {
  return date_;
}

Client *Realtor::getBuyer() const {
  return buyer_;
}

Client *Realtor::getSeller() const {
  return (sellers_.size() ? sellers_.top() : nullptr);
}

std::vector<Report> Realtor::getReports() const {
  return reports_;
}

// others

void Realtor::addSeller(Client *seller) {
  sellers_.push(seller);
} 

void Realtor::addReport(
  const Date &date, RealEstate *realEstate, Client *buyer, long revenue
){
  reports_.push_back(Report(date, realEstate, buyer, revenue));
}

Client *Realtor::searchBuyer() {
  int chanceToFindBuyer = asymp(experience_, 5, 7, 2);

  if (chance(chanceToFindBuyer)) {
    return agency_->generateBuyer();
  }

  return nullptr;
}

Client *Realtor::searchSeller() {
  int chanceToFindSeller = asymp(experience_, 7, 10, 2);

  if (chance(chanceToFindSeller)) {
    return agency_->getAvailableSeller();
  }

  return nullptr;
}

void Realtor::work() {
  Client *buyer;
  Client *seller; 

  if (!buyer_) {
    buyer = agency_->getBuyer();

    if (!buyer) {
      seller = agency_->getSeller();
    }

    // случай елси в агенство обратился клие/нт
    if (buyer || seller) {
      date_.addMinutes(Random::getInt(0, 59));
      std::cout 
        << "[ " << date_ << " ][ " << getFullName() << " ]: "
        << "В агенство обратился клиент желающий ";

      if (buyer) {
        std::cout << "приобрести/снять";
      } else {
        std::cout << "продать/арендовать";
      }

      std::cout << " недвижимость. Начиная им заниматься.\n";  
    } else {
      if (!isSearching_) {
        date_.addMinutes(Random::getInt(0, 59));
        std::cout 
          << "[ " << date_ << " ][ " << getFullName() << " ]: "
          << "Поиск клиентов.\n";

        isSearching_ = true;
      } 

      buyer = searchBuyer();

      if (!buyer) {
        seller = searchSeller();
      }

      // случай если риэлтор сам ищет клиентов
      if (buyer || seller) {
        date_.addMinutes(Random::getInt(0, 59));

        std::cout 
          << "[ " << date_ << " ][ " << getFullName() << " ]: "
          << "Найден клиент желающий ";

        if (buyer) {
          std::cout << "приобрести/снять";
        } else {
          std::cout << "продать/арендовать";
        }

        std::cout << " недвижимость. Начиная им заниматься.\n"; 

        isSearching_ = false; 
      }
    }

    if (buyer || seller) {
      date_.addMinutes(Random::getInt(60, 120));
      std::cout << "[ " << date_ << " ][ " << getFullName() << " ]: ";

      if (chance(chanceToConcludeContract_)) {
        std::cout << "Контракт с клиентом успешно заключен.\n";

        contractConcluded_ = true;
      } else {
        std::cout << "Неудалось заключить контракт. Подолжаю поиск клиентов.\n";
      }
    }

    if (contractConcluded_)  {
      date_.addMinutes(Random::getInt(60, 120));
      std::cout << "[ " << date_ << " ][ " << getFullName() << " ]: ";
      
      if (buyer) {
        std::cout << "Узнал подробности о желаемой недвижимости у клиента. Приступаю к поиску подходящих вариантов.\n";

        buyer_ = buyer;
      } else {
        std::cout << "Узнал характеристики недвижимости и занес клиента в базу данных. Продолжаю поиск клиентов.\n";

        agency_->addAvailableSeller(seller);
      } 

      contractConcluded_ = false;
    }
    
  } else {
    if (allSellersFound_) {
      if (!isViewing_) {
        date_.addMinutes(Random::getInt(0, 59));
        std::cout << "[ " << date_ << " ][ " << getFullName() << " ]: " 
          << "Подходящие варинаты найдеты. Начинаяю "; 
        
      }
      
    } else {
      if (sellers_.size() < maxSellers_) {
        seller = searchSeller();

        if (seller) {
          date_.addMinutes(Random::getInt(0, 59));
          std::cout << "[ " << date_ << " ][ " << getFullName() << " ]: " 
            << "Найден подходящий вариант недвижимости для клиента. Осталось найти: " 
            << (maxSellers_ - sellers_.size()) << "\n";

          addSeller(seller);
        }

      } else {
        allSellersFound_ = true;
      }
    }
  }
  
  // int days = 30 - asymp(charisma_, experience_, 30, 0.5) 
  //   + ((buyer->getRealEstate()->getSaleType() == 0) ? 5 : 0);
}

std::ostream& Realtor::print(std::ostream &out) const {
  Realtor::Person::print(out);

  out << "Опыт: " << experience_ << "\n"
      << "Харизма: " << charisma_ << "\n"
      << "Зарплата: " << salary_ << "\n";

  return out;
}