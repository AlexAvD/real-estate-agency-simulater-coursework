#include "Flat.h"

const std::vector<std::string> Flat::layouts_ = {
  "Гостинка", "Малосемейка", "Студия", "Частичная студия", 
  "С Изолированными комнатами", "Со смежными комнатами"
};

Flat::Flat() : RealEstate() {
  floor_ = 0;
  newBuilding_ = false;
  balcony_ = false;
  lift_ = false;
  layout_ = "";
}

Flat::Flat(const Flat &flat) : RealEstate(flat) {
  floor_ = flat.floor_;
  newBuilding_ = flat.newBuilding_;
  balcony_ = flat.balcony_;
  lift_ = flat.lift_;
  layout_ = flat.layout_;
}

Flat Flat::generate() {
  Flat flat;

  flat.setRandomProperties();

  return flat;
}

void Flat::getFlatsFromFile(const std::string &pathToFile, std::stack<Flat> *dist) {	
	std::vector<std::map<std::string, std::string>> data = handleFile(pathToFile, ':');
	std::map<std::string, std::string> remainingProperties;
	
	for (auto &dataItem : data) {
		if (dataItem.find("Тип") != dataItem.end()) {
			if (RealEstate::isFlat(dataItem["Тип"])) {
				Flat flat;
	
				remainingProperties = flat.setProperties(dataItem);

				dist->push(flat);

        if (remainingProperties.size()) {
          for (const auto &[key, val] : remainingProperties) {
            std::cerr << colorred << "Поля \"" << key << "\" в объекте \"Flat\" не существует\n" << endcolor;
          }
        }	
			} 			
		} else {
      std::cerr << colorred << "Не найдено ключевое поле \"Тип\"\n" << endcolor;
    }
	}
}

// setters
void Flat::setFloor(int floor) {
  floor_ = floor;
}

void Flat::setNewBuilding(bool newBuilding) {
  newBuilding_ = newBuilding;
}

void Flat::setBalcony(bool balcony) {
  balcony_ = balcony;
}

void Flat::setLift(bool lift) {
  lift_ = lift;
}

void Flat::setLayout(std::string layout) {
  layout_ = layout;
}

std::map<std::string, std::string> 
Flat::setProperties(const std::map<std::string, std::string> &proprerties) {
  std::map<std::string, std::string> remainingProperties;

  for (const auto &[key, val] : Flat::RealEstate::setProperties(proprerties)) {
    if (key == "Этаж") {
      setFloor(std::stoi(val));
    } else if (key == "Новостройка") {
      setNewBuilding(isTrueWord(val));
    } else if (key == "Балкон") {
      setBalcony(isTrueWord(val));
    } else if (key == "Лифт") {
      setLift(isTrueWord(val));
    } else if (key == "Планировка") { 
      setLayout(val);
    } else {
      remainingProperties[key] = val;
    }
  }

  return remainingProperties;
}

// getters
int Flat::getFloor() const {
  return floor_;
}

bool Flat::getNewBuilding() const {
  return newBuilding_;
}

bool Flat::getBalcony() const {
  return balcony_;
}

bool Flat::getLift() const {
  return lift_;
}

std::string Flat::getLayout() const {
  return layout_;
}

// others
void Flat::setRandomProperties() {
  Flat::RealEstate::setRandomProperties(0);

  int floors = getFloors();
  setFloor(Random::getInt(1, floors));

  int buildYear = getBuildYear();
  setNewBuilding(isBetween(buildYear, 2016, 2019) ? true : false);

  int lift = (floors <= 10) ? Random::getBool() : true;
  setLift(lift);

  setBalcony(Random::getBool());
  setLayout(layouts_[Random::getInt(0, layouts_.size() - 1)]);
}

std::ostream &Flat::print(std::ostream &out) const {
  int saleType = getSaleType();

  Flat::RealEstate::print(out);

  out 
    << li << "Этаж: " << floor_ << '\n'
    << li << "Новостройка: " << (newBuilding_ ? "Да" : "Нет")  << '\n'
    << li << "Балкон: " << (balcony_ ? "Есть" : "Нет") << '\n'
    << li << "Лифт: " << (lift_ ? "Есть" : "Нет") << '\n'  
    << li << "Планировка: " << layout_ << '\n';

  if (saleType != -1) {
    std::string saleTypeStr = (saleType == 0) ? "Продажа" : ( (saleType == 1) ? "Аренда" : "" );

    out << li << "Тип продажи: " << saleTypeStr << '\n';
  }
    
  out << li << "Цена: " << getPrice() << " руб." << '\n';

  return out;
}