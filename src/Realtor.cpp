#include "Realtor.h"

Realtor::Realtor() : Person() {
  experience_ = 0;
  charisma_ = 0.5;
  currentReport_ = nullptr;
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
  currentReport_ = realtor.currentReport_;
  currentBuyer_ = realtor.currentBuyer_;
  currentSeller_ = realtor.currentSeller_;
  agency_ = realtor.agency_;
}

Realtor Realtor::generate() {
  Realtor realtor;

  realtor.setRandomProperties();

  return realtor;
}

void Realtor::getRealtorsFromFile(const std::string &pathToFile, std::stack<Realtor> *dist) {
	std::vector<std::map<std::string, std::string>> data = handleFile(pathToFile, ':');
	
	Realtor tmp;

	for (auto &vItem : data) {
		for (const auto &[key, val] : vItem) {
			if (key == "Имя") {
				tmp.setName(val);
			} else if (key == "Фамилия") {
				tmp.setSurname(val);
			} else	if (key == "Фамилия") {
				tmp.setSurname(val);
			} else if (key == "ФИО") {
				tmp.setFullName(val);
			} else if (key == "Пол") {
				tmp.setGender(val);
			} else if (key == "Возраст") {
				tmp.setAge(val);
			} else if (key == "Паспортные данные") {
				tmp.setPassportData(val);
			} else if (key == "Зарплата") {
				tmp.setSalary(val);
			} else if (key == "Деньги") {
				tmp.setMoney(val);
			} else if (key == "Опыт") {
				tmp.setExperience(val);
			} else if (key == "Харизма") {
				tmp.setCharisma(val);
			}
		}

		dist->push(tmp);
	}
}

// setters

void Realtor::setExperience(int experience) {
  experience_ = experience;
}

void Realtor::setExperience(const std::string &experience) {
  experience_ = std::stoi(experience);
}

void Realtor::setCharisma(float charisma) {
  charisma_ = charisma;
}

void Realtor::setCharisma(const std::string &charisma) {
  charisma_ = std::stof(charisma);
}

void Realtor::setDate(const Date &date) {
  date_ = date;
}

void Realtor::setCurrentReport(const Report &report) {
  reports_.push_back(report);

  currentReport_ = &reports_.back();
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

Date Realtor::getDate() const {
  return date_;
}

Buyer *Realtor::getCurrentBuyer() const {
  return currentBuyer_;
}

Seller *Realtor::getCurrentSeller() const {
  return currentSeller_;
}

void Realtor::setRandomProperties() {
  Realtor::Person::setRandomProperties();

  setExperience(Random::getInt(0, (getAge() - 25)));
  setCharisma(Random::getInt(20 + getExperience() * 2, 90) / 100.);
}


void Realtor::searchClient() {
  Buyer *buyer;
  Seller *seller;

  if (!currentClient_) {
    std::cout << "[" << date_ << "]: " << "Поиск клиентов...";
   
    buyer = searchBuyer();

    if (buyer) {
      currentClient_ = buyer;
      currentBuyer_ = buyer;
    } else {
      seller = searchSeller();

      if (seller) {
        currentClient_ = seller;
        currentSeller_ = seller;
      }
    }
  } else {
    int currentClientType = currentBuyer_->getType();

    if (!currentBuyer_) {
      std::cout << "[" << date_ << "]: " << "Поиск "
        << ((currentClientType == 0) ? "покупателя" : "арендодателя") << "...";

      buyer = searchBuyer();

      if (buyer) {
        currentBuyer_ = buyer;
      }
    } else if (!currentSeller_) {
      
      std::cout << "[" << date_ << "]: " << "Поиск "
        << ((currentClientType == 2) ? "продовца" : "арендатора") << "...";

      seller = searchSeller();

      if (seller) {
        currentSeller_ = seller;
      }
    } else {

    }
  }
}



Buyer* Realtor::searchBuyer() {
  int chanceToFind = asymp(experience_, 10, 40, 2);

  if (chance(chanceToFind)) {
    Buyer buyer = Buyer::generate();

    date_.setMinute(Random::getInt(10, 59));

    std::cout << "[" << date_ << "]: " << "Найден " << buyer.getTypeAsString() << '\n';

    agency_->addBuyer(buyer);

    return agency_->getLastAddedBuyer();
  }

  return nullptr;
}

Seller *Realtor::searchSeller() {
  if (!currentSeller_) {
    int percent = asymp(experience_, 20, 60, 2);

    if (chance(percent)) {
      Seller seller = Seller::generate();

      date_.setMinute(Random::getInt(10, 59));

      std::cout << "[" << date_ << "]: " << "Найден " << seller.getTypeAsString() << '\n';

      agency_->addSeller(seller);
      currentSeller_ = agency_->getLastAddedSeller();
    }
  }

  return nullptr;
}

// others

void Realtor::addToReport(const Date &date, const std::string &action) {
  if (currentReport_) {
    currentReport_->addToHistory(date, action);
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

std::ostream& Realtor::print(std::ostream &out) const {
  Realtor::Person::print(out);

  out 
    << "Опыт: " << experience_ 
    << '\n'
    << "Харизма: " << charisma_;

  return out;
}