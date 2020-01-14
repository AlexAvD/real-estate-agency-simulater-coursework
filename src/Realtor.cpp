#include "Realtor.h"

Realtor::Realtor() : Person() {
  experience_ = 0;
  charisma_ = 0.5;
  salary_ = 0;

  maxSuitableSellers_ = 3;

  didContractConclude_ = false;
  isSearching_ = false;
  isSearchingSuitable_ = false;
  isReviewing_ = false;
  isSuitableSellersFound_ = false;
  isBuyerFound_ = false;
  isSellerFound_ = false;
  isClientFound_ = false;

  date_ = Date("", "07:00:00");
  agency_ = nullptr;
  currentBuyer_ = Client();
  currentSeller_ = Client();
}

Realtor::Realtor(const Realtor &realtor) : Person(realtor) {  
  experience_ = realtor.experience_;
  charisma_ = realtor.charisma_;
  salary_ = realtor.salary_;

  maxSuitableSellers_ = realtor.maxSuitableSellers_;

  didContractConclude_ = realtor.didContractConclude_;
  isSearching_ = realtor.isSearching_;
  isSearchingSuitable_ = realtor.isSearchingSuitable_;
  isSuitableSellersFound_ = realtor.isSuitableSellersFound_;
  isReviewing_ = realtor.isReviewing_;
  isBuyerFound_ = realtor.isBuyerFound_;
  isSellerFound_ = realtor.isSellerFound_;
  isClientFound_ = realtor.isClientFound_;

  date_ = realtor.date_;
  agency_ = realtor.agency_;
  currentBuyer_ = realtor.currentBuyer_;
  currentSeller_ = realtor.currentSeller_;
  
  suitableSellers_ = realtor.suitableSellers_;
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

void Realtor::setCurrentBuyer(const Client &buyer) {
  currentBuyer_ = buyer;
}

void Realtor::setCurrentSeller(const Client &seller) {
  currentSeller_ = seller;
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

int Realtor::getChanceToFindBuyer() const {
  return asymp(experience_, 5, 7, 2);
}

int Realtor::getChanceToFindSeller() const {
  return asymp(experience_, 7, 10, 2);
}

int Realtor::getChanceToConludeRealtorContract() const {
  return 80;
}

int Realtor::getChanceThatBuyerMakePurchase() const {
  return 70;
}

float Realtor::getCharisma() const {
  return charisma_;
}

Date Realtor::getDate() const {
  return date_;
}

Client Realtor::getCurrentBuyer() const {
  return currentBuyer_;
}

Client Realtor::getCurrentSeller() const {
  return currentSeller_;
}

Client Realtor::getSuitableSeller() {
  Client sSeller = suitableSellers_.top();

  suitableSellers_.pop();

  return sSeller;
}

std::vector<Report> Realtor::getReports() const {
  return reports_;
}

// others

void Realtor::addSuitableSeller(const Client &seller) {
  suitableSellers_.push(seller);
} 

void Realtor::addReport(
  const Date &date, RealEstate *realEstate, Client *buyer, long revenue
){
  reports_.push_back(Report(date, realEstate, buyer, revenue));
}

void Realtor::handleAppeals() {
  date_.addMinutes(Random::getInt(0, 59));

  std::cout 
    << "[ " << date_ << " ][ " << getFullName() << " ]: "
    << "В агенство обратился клиент, ";

  if (agency_->didBuyerAppeal()) {
    currentBuyer_ = agency_->getAppealedBuyer();
    isBuyerFound_ = isClientFound_ = true;

    std::cout << currentBuyer_.getFullName() << ", желающий приобрести/снять";

  } else if (agency_->didSellerAppeal()) {
    currentSeller_ = agency_->getAppealedSeller();
    isBuyerFound_ = isClientFound_ = true;
    
    std::cout << currentSeller_.getFullName() << ", желающий продать/арендовать";
  }

  std::cout << " недвижимость. Начиная им заниматься.\n";  
}

void Realtor::searchClients() {
  if (!isSearching_) {
    date_.addMinutes(Random::getInt(0, 59));
      std::cout 
        << "[ " << date_ << " ][ " << getFullName() << " ]: "
        << "Поиск клиентов.\n";

    isSearching_ = true;
  } else {
    if (chance(getChanceToFindBuyer())) {
      currentBuyer_ = agency_->generateBuyer();
      isBuyerFound_ = true;
      isClientFound_ = true;
    } else if (chance(getChanceToFindSeller())) {
      currentSeller_ = agency_->generateSeller();
      isSellerFound_ = true;
      isClientFound_ = true;
    }

    if (isClientFound_) {
      isSearching_ = false;

      date_.addMinutes(Random::getInt(30, 59));
      std::cout 
          << "[ " << date_ << " ][ " << getFullName() << " ]: "
          << "Найден клиент, ";

      if (isBuyerFound_) {
        std::cout << currentBuyer_.getFullName() << ", желающий приобрести/снять";
      } else if (isClientFound_) {
        std::cout << currentSeller_.getFullName() << ", желающий продать/арендовать";
      }

      std::cout << " недвижимость. Начинаю им заниматься.\n";
    }
  }
}

void Realtor::concludeRealtorContract() {
  date_.addMinutes(Random::getInt(60, 120));
    std::cout << "[ " << date_ << " ][ " << getFullName() << " ]: ";

  if (chance(getChanceToConludeRealtorContract())) {
    std::cout << "Контракт с клиентом успешно заключен.\n";

    didContractConclude_ = true;
  } else {
    std::cout << "Неудалось заключить контракт с клиентом. Подолжаю поиск.\n";

    if (isBuyerFound_) {
      isBuyerFound_ = false;
    } else if (isSellerFound_) {
      isSellerFound_ = false;
    }

    isClientFound_ = false;
    isSearching_ = true;
  }
}


void Realtor::handleSeller() {
  date_.addMinutes(Random::getInt(60, 120));
  std::cout 
    << "[ " << date_ << " ][ " << getFullName() << " ]: "
    << "Узнал характеристики недвижимости и занес клиента в базу данных. Продолжаю поиск клиентов.\n";

  agency_->addAvailableSeller(currentSeller_);
  isSearching_ = true;
  isClientFound_ = false;
  isSellerFound_ = false;
  didContractConclude_ = false;
}


void Realtor::searchSuitableSellers() {
  if (isSearchingSuitable_) {
    if ((int)suitableSellers_.size() < maxSuitableSellers_) {
      if (chance(getChanceToFindSeller())) {
        addSuitableSeller(agency_->getAvailableSeller());
        isSellerFound_ = true;
      }

      if (isSellerFound_) {
        date_
          .addDays(Random::getInt(1, 2))
          .setHour(Random::getInt(8, 16))
          .setMinute(Random::getInt(0, 59));

        std::cout << "[ " << date_ << " ][ " << getFullName() << " ]: " 
          << "Найден подходящий вариант недвижимости для клиента. Осталось найти: " 
          << (maxSuitableSellers_ - suitableSellers_.size()) << "\n";

        isSellerFound_ = false;
      }
    } else {
      isSearchingSuitable_ = false;
      isSuitableSellersFound_ = true;
    }
  } else {
    date_.addMinutes(Random::getInt(0, 59));
    std::cout << "[ " << date_ << " ][ " << getFullName() << " ]: " 
      << "Приступаю к поиску подходящих вариантов.\n"; 

    isSearchingSuitable_ = true;
  }
}

void Realtor::clearSuitableSellers() {
  while (!suitableSellers_.empty()) {
    agency_->addAvailableSeller(getSuitableSeller());
  }
}

void Realtor::concludeAssignmentContract() {
  date_
    .addDays(Random::getInt(3, 5))
    .setHour(Random::getInt(8, 16))
    .setMinute(Random::getInt(0, 59));

  std::cout 
    << "\n[ " << date_ << " ][ " << getFullName() << " ]: "
    << "Договор " 
    << ( (currentSeller_.getRealEstate()->getSaleType() == 0) ? "купли-продажи" : "аренды" )
    << " успешно заключен. Продолжаю поиск новых клиентов.\n";

  clearSuitableSellers();
  isReviewing_ = false;
  isSuitableSellersFound_ = false;
  isBuyerFound_ = false;
  isClientFound_ = false;
  didContractConclude_ = false;
}

void Realtor::reviewSuitableSellers() { 
  date_.addMinutes(Random::getInt(0, 59));
  std::cout << "[ " << date_ << " ][ " << getFullName() << " ]: " ;
    
  if (isReviewing_) {
   
    if (!suitableSellers_.empty()) {
      currentSeller_ = getSuitableSeller();

      if (chance(getChanceThatBuyerMakePurchase())) {        
        std::cout 
          << "Найден вариант, который клиент хочет приобрести: \n\n"
          << *currentSeller_.getRealEstate();

        concludeAssignmentContract();
      } else {
        if (suitableSellers_.empty()) {
          std::cout << "Клиенту не подошел ни один из предложенных вариантов.\n";
        } else {
          std::cout << "Клиенту не понравился один из вариантов. Продолжаем обход.\n";
        }
        
        agency_->addAvailableSeller(currentSeller_);
      }
    } else {
      std::cout << "Продолжаю поиск подходящих вариантов.\n";
      isReviewing_ = false;
      isSuitableSellersFound_ = false;
    }
  } else {
    std::cout << "Подходящие варинаты найдеты. Приступаем к их обходу.\n"; 

    isReviewing_ = true;
  }
}


void Realtor::handleBuyer() {
  if (isSuitableSellersFound_) {
    reviewSuitableSellers();
  } else {
    searchSuitableSellers();
  }
}

bool Realtor::isAgencyHasAppeals() {
  return agency_->hasAppeals();
}

void Realtor::work() {
  if (isClientFound_) {
    if (didContractConclude_) {
      if (isBuyerFound_) {
        handleBuyer();
      } else if (isSellerFound_) {
        handleSeller();
      }
    } else {
      concludeRealtorContract();
    }
  } else {
    if (isAgencyHasAppeals()) {
      handleAppeals();
    } else {
      searchClients();
    }
  }
  
  // int days = 30 - asymp(charisma_, experience_, 30, 0.5) 
  //   + ((buyer->getRealEstate()->getSaleType() == 0) ? 5 : 0);
}

std::ostream& Realtor::print(std::ostream &out) const {
  Realtor::Person::print(out);

  out << li << "Опыт: " << experience_ << "\n"
      << li << "Харизма: " << charisma_ << "\n"
      << li << "Зарплата: " << salary_ << "\n";

  return out;
}