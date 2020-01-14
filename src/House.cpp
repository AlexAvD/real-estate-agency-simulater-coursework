#include "House.h"

const std::vector<std::string> House::materials_ = {
  "Монолитный кирпич",
  "Дерево",
  "Кирпич",
  "Монолит",
  "Панель",
  "Ячеистый бетон"
};

House::House() : RealEstate() {
  plotArea_ = 0;
  garage_ = false;
  material_ = "";
}

House::House(const House &house) : RealEstate(house) {
  plotArea_ = house.plotArea_;
  garage_ = house.garage_;
  material_ = house.material_;
}

House House::generate() {
  House house;

  house.setRandomProperties();

  return house;
}

void House::getHousesFromFile(const std::string &pathToFile, std::stack<House> *dist) {	
	std::vector<std::map<std::string, std::string>> data = handleFile(pathToFile, ':');
	std::map<std::string, std::string> remainingProperties;
	
	for (auto &dataItem : data) {
		if (dataItem.find("Тип") != dataItem.end()) {
			if (RealEstate::isHouse(dataItem["Тип"])) {
				House house;
	
				remainingProperties = house.setProperties(dataItem);

				dist->push(house);

        if (remainingProperties.size()) {
          for (const auto &[key, val] : remainingProperties) {
            std::cerr << colorred << "Поля \"" << key << "\" в объекте \"House\" не существует\n" << endcolor;
          }
			  }	
			}

		} else {
      std::cerr << colorred << "Не найдено ключевое поле \"Тип\"\n" << endcolor;
    }
	}
}

// setters

void House::setGarage(bool garage) {
  garage_ = garage;
}

void House::setMaterial(const std::string &material) {
  material_ = material;
}

void House::setPlotArea(int plotArea) {
  plotArea_ = plotArea;
}

void House::setRandomProperties() {
  House::RealEstate::setRandomProperties(1);

  material_ = materials_[Random::getInt(0, materials_.size() - 1)];
  garage_ = Random::getBool();
  plotArea_ = Random::getInt(100, 500);
}

std::map<std::string, std::string> 
House::setProperties(const std::map<std::string, std::string> &proprerties) {
  std::map<std::string, std::string> remainingProperties;

  for (const auto &[key, val] : (House::RealEstate::setProperties(proprerties))) {
    if (key == "Материал") {
      setMaterial(val);
    } else if (key == "Площадь участка") {
      setPlotArea(std::stoi(val));
    } else if (key == "Гараж") {
      setGarage(isTrueWord(val));
    } else {
      remainingProperties[key] = val;
    }
  }

  return remainingProperties;
}


// getters

int House::getPlotArea() const {
  return plotArea_;
}

bool House::getGarage() const {
  return garage_;
}

std::string House::getMaterial() const {
  return material_;
}

// others

std::ostream &House::print(std::ostream &out) const {
  int saleType = getSaleType();
 
  House::RealEstate::print(out);

  out 
    << li << "Материал: " << material_ << "\n"
    << li << "Площадь участка: " << plotArea_ << " м^2\n" 
    << li << "Гараж: " << ((garage_) ? "Есть" : "Нет") << "\n";

  if (saleType != -1) {
    std::string saleTypeStr = (saleType == 0) ? "Продажа" : ( (saleType == 1) ? "Аренда" : "" );

    out << li << "Тип продажи: " << saleTypeStr << '\n';
  }
    
  out << li << "Цена: " << getPrice() << " руб." << '\n';

  return out;
}
