#include "RealEstate.h"

const std::vector<std::pair<std::string, std::vector<std::string>>> RealEstate::districtsAndStreets_ = {
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

const std::vector<std::vector<std::string>> RealEstate::types_ = {
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
  street_   = "";
  district_ = "";
  type_ = "";
  area_ = 0;
  buildYear_ = 0;
  floors_ = 0;
  rooms_ = 0;
  saleType_ = -1;
  price_ = 0;
  furniture_ = false;
  repair_ = false;
}

RealEstate::RealEstate(const RealEstate & realEstate) {
  street_     = realEstate.street_;
  district_   = realEstate.district_;
  type_       = realEstate.type_;
  area_       = realEstate.area_;
  buildYear_  = realEstate.buildYear_;
  floors_     = realEstate.floors_;
  rooms_      = realEstate.rooms_;
  price_      = realEstate.price_;
  furniture_  = realEstate.furniture_;
  repair_     = realEstate.repair_;
  saleType_   = realEstate.saleType_;
}

RealEstate::~RealEstate() {

}

bool RealEstate::isFlat(const std::string &typeOfRealEstate) {
  for (const std::string &type : types_[0]) {
    if (typeOfRealEstate == type) {
      return true;
    }
  }

  return false;
}

bool RealEstate::isHouse(const std::string &typeOfRealEstate) {
   for (const std::string &type : types_[1]) {
    if (typeOfRealEstate == type) {
      return true;
    }
  }

  return false;
}

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

void RealEstate::setRooms(int rooms) {
  rooms_ = rooms;
}

void RealEstate::setSaleType(int saleType) {
  saleType_ = saleType;
}

void RealEstate::setFurniture(bool furniture) {
  furniture_ = furniture;
}

void RealEstate::setRepair(bool repair) {
  repair_ = repair;
}

void RealEstate::setPrice(long price) {
  price_ = price;
}

void RealEstate::setStreet(const std::string &street) {
  street_ = street;
}

void RealEstate::setDistrict(const std::string &district) {
  district_ = district;
}

void RealEstate::setType(const std::string &type) {
  type_ = type;
}

void RealEstate::setRandomProperties(int typeOfConstruction) {
  int typesSize = types_.size() - 1;

  if (typeOfConstruction == -1 || !isBetween(typeOfConstruction, 0, typesSize)) {
    typeOfConstruction = Random::getInt(0, typesSize);
  }

  std::vector<std::string> type = types_[typeOfConstruction];
  setType(type[Random::getInt(0, type.size() - 1)]);

  int floors;
  int area;
  int rooms;
 
  if (typeOfConstruction == 0) {  
    floors = roundTo(Random::getInt(5, 25), 5);
    rooms = Random::getInt(1, 2);
    area = Random::getInt(40 * rooms, 100);
  } else if (typeOfConstruction == 1) {
    floors = Random::getInt(1, 4);
    rooms = Random::getInt(2, 4) * floors / 2;
    area = Random::getInt(50 * rooms, 400);
  }

  setFloors(floors);
  setArea(area);
  setRooms(rooms);

  std::pair<std::string, std::vector<std::string>> districtAndStreets = 
    districtsAndStreets_[Random::getInt(0, districtsAndStreets_.size() - 1)];
  std::string district = districtAndStreets.first;
  std::vector<std::string> streets = districtAndStreets.second;

  std::stringstream ss;

  ss 
    << streets[Random::getInt(0, streets.size() - 1)] 
    << ' ' 
    << Random::getInt(1, 300);

  setDistrict(district);
  setStreet(ss.str());
  setRepair(Random::getBool());
  setFurniture(Random::getBool());
  setBuildYear(2000 + Random::getInt(0, 19));
  setSaleType(Random::getInt(0, 1));

  if (saleType_ == 0) {
    setPrice(area_ * rooms_ * 10000);
  } else if (saleType_ == 1) {
    setPrice(area_ * rooms_ * 100);
  }
}

std::map<std::string, std::string> RealEstate::setProperties(const std::map<std::string, std::string> &proprerties) {
  std::map<std::string, std::string> remainingProperties;

  for (const auto &[key, val] : proprerties) {
    if (key == "Тип") {
      setType(val);
    } else if (key == "Район") {
      setDistrict(val);
    } else if (key == "Улица") {
      setStreet(val);
    } else if (key == "Год постройки") {
      setBuildYear(std::stoi(val));
    } else if (key == "Площадь") { 
      setArea(std::stoi(val));
    } else if (key == "Кол-во комнат") {
      setRooms(std::stoi(val));
    } else if (key == "Ремонт") {
      setRepair(isTrueWord(val));
    } else if (key == "Мебель") {
      setFurniture(isTrueWord(val));
    } else if (key == "Этажность") {
      setFloors(std::stoi(val));
    } else if (key == "Тип продажи") {
      if (val == "Продажа") {
        setSaleType(0);
      } else if (val == "Аренда") {
        setSaleType(1);
      }
    } else if (key == "Цена") {
      setPrice(std::stoi(val));
    } else {
      remainingProperties[key] = val;
    }
  }

  return remainingProperties;
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

int RealEstate::getRooms() const {
  return floors_;
}

bool RealEstate::getFurniture() const {
  return furniture_;
}

bool RealEstate::getRepair() const {
  return repair_;
}

int RealEstate::getSaleType() const {
  return saleType_;
}

long RealEstate::getPrice() const {
  return price_;
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

// operators

RealEstate &RealEstate::operator=(const RealEstate &realEstate) {
  street_     = realEstate.street_;
  district_   = realEstate.district_;
  type_       = realEstate.type_;
  area_       = realEstate.area_;
  buildYear_  = realEstate.buildYear_;
  floors_     = realEstate.floors_;
  rooms_      = realEstate.rooms_;
  price_      = realEstate.price_;
  furniture_  = realEstate.furniture_;
  repair_     = realEstate.repair_;
  saleType_   = realEstate.saleType_;

  return *this;
}

// others

std::ostream &RealEstate::print(std::ostream &out) const {
  out
    << li << "Тип: "            << type_ << '\n'
    << li << "Район: "          << district_ << '\n'
    << li << "Улица: "          << street_ << '\n'
    << li << "Год постройки: "  << buildYear_ << '\n'
    << li << "Площадь: "        << area_ << " м^2" << '\n'
    << li << "Кол-во комнат: "  << rooms_ << '\n'
    << li << "Ремонт: "         << (repair_ ? "Есть" : "Нет")  << '\n'
    << li << "Мебель: "         << (furniture_ ? "Есть" : "Нет") << '\n'
    << li << "Этажность: "      << floors_ << '\n';

  return out;
}

std::ostream &operator<<(std::ostream &out, const RealEstate &realEstate) {
  return realEstate.print(out);
}