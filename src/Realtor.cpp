#include "Realtor.h"

Realtor::Realtor() : Person() {
  experience_ = 0;
  charisma_ = 0.5;
  salary_ = 0;
  earnings_ = 0;
  
  didRealtorContractConclude_ = false;
  isSearching_ = false;
  isSearchingSuitables_ = false;
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
  earnings_ = realtor.earnings_;

  didRealtorContractConclude_ = realtor.didRealtorContractConclude_;
  isSearching_ = realtor.isSearching_;
  isSearchingSuitables_ = realtor.isSearchingSuitables_;
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
  logs_ = realtor.logs_;
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
Realtor::setProperties(const std::map<std::string, std::string> &properties) {
  std::map<std::string, std::string> remainingProperties;

  for (const auto &[key, val] : Realtor::Person::setProperties(properties)) {
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

  int minExperience = 0;
  int maxExperience = getAge() - 25;

  setExperience(Random::getInt(minExperience, maxExperience));

  int minSalary = 25000 + experience_ * 1000;
  int maxSalary = 30000 + experience_ * 2000;

  setSalary(roundTo(Random::getInt(minSalary, maxSalary), 100));

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

long Realtor::getEearnings() const {
  return earnings_;
}

int Realtor::getMaxSuitableSellers() const {
  return asymp(experience_, 3, 6, 10);
}

int Realtor::getChanceToFindBuyer() const {
  return asymp(experience_, 5, 7, 2);
}

int Realtor::getChanceToFindSeller() const {
  return asymp(experience_, 7, 10, 2);
}

int Realtor::getChanceToConludeRealtorContract() const {
  return charisma_ * 100;
}

int Realtor::getChanceThatBuyerMakePurchase() const {
  return experience_ * charisma_ + 50;
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

std::vector<std::string> &Realtor::getLogs() {
  return logs_;
}

// others

void Realtor::calcAndAddEarnings(Client *buyerPurchased) {
  RealEstate *realEstate = buyerPurchased->getRealEstate();
  
  float commision = 1;
  int saleType = realEstate->getSaleType();

  if (saleType == 0) {
    commision = agency_->getSaleCommision();
  } else if (saleType == 1) {
    commision = agency_->getRentCommision();
  }

  earnings_ += realEstate->getPrice() * commision * agency_->getRentCommision();
}

void Realtor::addSuitableSeller(const Client &seller) {
  suitableSellers_.push(seller);
} 

void Realtor::clearSuitableSellers() {
  while (!suitableSellers_.empty()) {
    agency_->addAvailableSeller(getSuitableSeller());
  }
}

void Realtor::log() {
  if (log_.str().size()) {
    logs_.push_back(log_.str());

    log_.str("");
  }
} 

void Realtor::handleAppeals() {
  date_.addMinutes(Random::getInt(0, 59));

  log_ 
    << "[ " << date_ << " ]: "
    << "В агентство обратился клиент, ";
  

  if (agency_->didBuyerAppeal()) {
    currentBuyer_ = agency_->getAppealedBuyer();
    isBuyerFound_ = isClientFound_ = true;

    log_ << currentBuyer_.getFullName() << ", желающий приобрести/снять";

  } else if (agency_->didSellerAppeal()) {
    currentSeller_ = agency_->getAppealedSeller();
    isBuyerFound_ = isClientFound_ = true;
    
    log_ << currentSeller_.getFullName() << ", желающий продать/арендовать";
  }

  log_ << " недвижимость. Начиная им заниматься.\n";  
}

void Realtor::searchClients() {
  if (!isSearching_) {
    date_.addMinutes(Random::getInt(0, 59));
      log_ 
        << "[ " << date_ << " ]: "
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
      log_ 
          << "[ " << date_ << " ]: "
          << "Найден клиент, ";

      if (isBuyerFound_) {
        log_ << currentBuyer_.getFullName() << ", желающий приобрести/снять";
      } else if (isSellerFound_) {
        log_ << currentSeller_.getFullName() << ", желающий продать/арендовать";
      }

      log_ << " Начинаю им заниматься.\n";
    }
  }
}

void Realtor::concludeRealtorContract() {
  date_.addMinutes(Random::getInt(60, 120));
    log_ << "[ " << date_ << " ]: ";

  if (chance(getChanceToConludeRealtorContract())) {
    log_ << "Контракт с клиентом успешно заключен.\n";

    didRealtorContractConclude_ = true;
  } else {
    log_ << "Не удалось заключить контракт. Продолжаю поиск клиентов.\n";

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
  log_ 
    << "[ " << date_ << " ]: "
    << "Узнал характеристики недвижимости и занес клиента в базу данных. Продолжаю поиск клиентов.\n";

  agency_->addAvailableSeller(currentSeller_);
  isSearching_ = true;
  isClientFound_ = false;
  isSellerFound_ = false;
  didRealtorContractConclude_ = false;
}


void Realtor::searchSuitableSellers() {
  if (isSearchingSuitables_) {

    if ((int)suitableSellers_.size() < getMaxSuitableSellers()) {
      if (chance(getChanceToFindSeller())) {
        addSuitableSeller(agency_->getAvailableSeller());
        isSellerFound_ = true;
      }

      if (isSellerFound_) {
        date_.addMinutes(Random::getInt(0, 59));

        log_ << "[ " << date_ << " ]: " 
          << "Найден подходящий вариант недвижимости для клиента. Осталось найти: " 
          << (getMaxSuitableSellers() - suitableSellers_.size()) << "\n";

        isSellerFound_ = false;
      }
    } else {
      isSearchingSuitables_ = false;
      isSuitableSellersFound_ = true;
    }
  } else {
    isSearchingSuitables_ = true;
  }
}

void Realtor::concludeAssignmentContract() {
  date_
    .addDays(Random::getInt(3, 5))
    .setHour(Random::getInt(8, 16))
    .setMinute(Random::getInt(0, 59));

  RealEstate *sellerRealEstate = currentSeller_.getRealEstate();
  int saleType = sellerRealEstate->getSaleType();
  
  log_ 
    << "\n[ " << date_ << " ]: "
    << "Договор " 
    << ( (saleType == 0) ? "купли-продажи" : "аренды" )
    << " успешно заключен. Продолжаю поиск новых клиентов.\n";

  // перенес недвижисоть с продоца на покупателя  
  currentBuyer_.setRealEstate(sellerRealEstate);
  currentSeller_.setRealEstate(nullptr);

  // сапись в вектор покупателя, который приобрел недвижимость
  agency_->addBuyersPurchased(currentBuyer_);
  calcAndAddEarnings(&currentBuyer_);

  clearSuitableSellers();
  isReviewing_ = false;
  isSuitableSellersFound_ = false;
  isBuyerFound_ = false;
  isClientFound_ = false;
  didRealtorContractConclude_ = false;
}

void Realtor::reviewSuitableSellers() { 
  date_.addMinutes(Random::getInt(0, 59));
  log_ << "[ " << date_ << " ]: " ;
    
  if (isReviewing_) {
    if (!suitableSellers_.empty()) {
      currentSeller_ = getSuitableSeller();

      if (chance(getChanceThatBuyerMakePurchase())) {        
        log_ 
          << "Найден вариант, который клиент хочет приобрести: \n\n"
          << *currentSeller_.getRealEstate();

        concludeAssignmentContract();
      } else {
        if (suitableSellers_.empty()) {
          log_ << "Клиенту не подошел ни один из предложенных вариантов.\n";
        } else {
          log_ << "Клиенту не понравился один из вариантов. Продолжаем обход.\n";
        }
        
        agency_->addAvailableSeller(currentSeller_);
      }
    } else {
      log_ << "Продолжаю поиск подходящих вариантов.\n";
      isReviewing_ = false;
      isSuitableSellersFound_ = false;
    }
  } else {
    log_ << "Подходящие варианты найдены. Приступаем к их обходу.\n"; 

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
    if (didRealtorContractConclude_) {
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

  log();
}

std::ostream& Realtor::print(std::ostream &out) const {
  Realtor::Person::print(out);

  out << li << "Опыт: " << experience_ << "\n"
      << li << "Харизма: " << charisma_ << "\n"
      << li << "Зарплата: " << salary_ << "\n";

  return out;
}