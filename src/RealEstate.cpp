#include "RealEstate.h"

std::vector<std::pair<std::string, std::vector<std::string>>> RealEstate::districtsAndStreets_ = {
  {
    "Ворошиловский",
    {
      "Чугуевская, ул.", "Нежинская, ул.", "Волкова, ул.", 
      "Харьковская, ул.", "Шелковая, ул.", "Евдокимова, ул." 
    }
  },
  {
    "Железнодорожный",
    {
      "Товарищеская, ул.", "Нижняя Балка, ул.", "Балашовская, ул.", 
      "Вольская, ул.", "Смоленская, ул.", "Фестивальная, ул."
    } 
  },
  {
    "Кировский",
    {
      "Донская, ул.", "Черниговская, ул.", "Гоголевская, ул.", 
      "Красноармейская, ул.", "Восточная, ул.", "Береговая, ул."
    }
  },
  {
    "Ленинский",
    {
      "Ульяновская, ул.", "Малюгиной, ул.", "Катаева, ул.", 
      "Зоологическая, ул.", "Ивановского, ул.", "Лермонтовская, ул."
    }
  }
};

std::vector<std::vector<std::string>> RealEstate::types_ = {
  {
    "Квартира",
    "Комната"
  },
  {
    "Дом",
    "Дача",
    "Коттедж",
    "Таунхаус"
  }
};

RealEstate::RealEstate() {
  street_ = "";
  district_ = "";
  type_ = "";
  area_ = 0;
  buildYear_ = 0;
  floors_ = 0;
  furniture_ = false;
  owner_ = nullptr;
}

RealEstate::RealEstate(
  std::string type, std::string street, std::string district, 
  int area, int buildYear, Person * owner
) {
  street_ = street;
  district_ = district;
  type_ = type;
  area_ = area;
  buildYear_ = buildYear;
  owner_ = owner;
}

RealEstate::RealEstate(const RealEstate & realEstate) {
  street_ = realEstate.street_;
  district_ = realEstate.district_;
  type_ = realEstate.type_;
  area_ = realEstate.area_;
  buildYear_ = realEstate.buildYear_;
  owner_ = realEstate.owner_;
}

/* std::vector<std::vector<std::string>> *RealEstate::getTypes() {
  return &types_;
}

std::vector<std::pair<std::string, std::vector<std::string>>> *RealEstate::getDistrictsAndStreets() {
  return &districtsAndStreets_;
} */

// setters
void RealEstate::setArea(int area) {
  area_ = area;
}

void RealEstate::setBuildYear(int year) {
  buildYear_ = year;
}

void RealEstate::setFloors(int floors) {
  floors_ = floors;
}

void RealEstate::setFurniture(bool furniture) {
  furniture_ = furniture;
}

void RealEstate::setRepair(bool repair) {
  repair_ = repair;
}

void RealEstate::setStreet(std::string street) {
  street_ = street;
}

void RealEstate::setDistrict(std::string district) {
  district_ = district;
}

void RealEstate::setType(std::string type) {
  type_ = type;
}

void RealEstate::setOwner(Person *person) {
  owner_ = person;
}

std::ostream &operator<<(std::ostream &out, const RealEstate &realEstate) {
  return realEstate.print(out);
}

// getters
int RealEstate::getArea() const {
  return area_;
}

int RealEstate::getBuildYear() const {
  return buildYear_;
}

int RealEstate::getFloors() const {
  return floors_;
}

bool RealEstate::getFurniture() const {
  return furniture_;
}

bool RealEstate::getRepair() const {
  return repair_;
}

std::string RealEstate::getStreet() const {
  return street_;
}

std::string RealEstate::getDistrict() const {
  return district_;
}

std::string RealEstate::getType() const {
  return type_;
}

RealEstate &RealEstate::setRandomProperties(int typeOfConstruction) {
  int typesSize = types_[0].size();

  if (!isBetween<int>(typeOfConstruction, 0, typesSize - 1)) {
    typeOfConstruction = Random::getInt(0, typesSize - 1);
  }

  std::vector<std::string> type = types_[typeOfConstruction];
  setType(type[Random::getInt(0, type.size() - 1)]);

  int floors;
  int area;
 
  if (typeOfConstruction == 0) {  
    floors = roundTo(Random::getInt(5, 25), 5);
    area = Random::getInt(20, 50);
  } else if (typeOfConstruction == 1) {
    floors = Random::getInt(1, 4);
    area = Random::getInt(100, 300);
  }

  setFloors(floors);
  setArea(area);

  std::pair<std::string, std::vector<std::string>> districtAndStreets = 
    districtsAndStreets_[Random::getInt(0, districtsAndStreets_.size() - 1)];
  std::string district = districtAndStreets.first;
  std::vector<std::string> streets = districtAndStreets.second;

  std::stringstream ss;
  ss << streets[Random::getInt(0, streets.size() - 1)] << ' ' << Random::getInt(1, 300);

  setDistrict(district);
  setStreet(ss.str());
  setRepair(Random::getBool());
  setFurniture(Random::getBool());
  setBuildYear(2000 + Random::getInt(0, 19));

  return *this;
}

std::ostream &RealEstate::print(std::ostream &out) const {
  out
    << "Тип: " << type_ << '\n'
    << "Район: " << district_ << '\n'
    << "Улица: " << street_ << '\n'
    << "Владелец: " << ((owner_ == nullptr) ? "" : owner_->getFullName()) << '\n'
    << "Год постройки: " << buildYear_ << '\n'
    << "Площадь: " << area_ << " м^2" << '\n'
    << "Ремонт: " << (repair_ ? "Есть" : "Нет")  << '\n'
    << "Мебель: " << (furniture_ ? "Есть" : "Нет") << '\n'
    << "Этажность: " << floors_ << '\n';

  return out;
}

