#include "Flat.h"

const std::vector<std::string> Flat::layouts_ = {
  "Гостинка", "Малосемейка", "Студия", "Частичная студия", 
  "С Изолированными комнатами", "Со смежными комнатами"
};

Flat::Flat() {
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

Flat &Flat::setRandomProperties() {
  Flat::RealEstate::setRandomProperties(0);

  int floors = getFloors();
  setFloor(Random::getInt(1, floors));

  int buildYear = getBuildYear();
  setNewBuilding(isBetween(buildYear, 2016, 2019) ? true : false);

  int lift = (floors <= 5) ? Random::getBool() : true;
  setLift(lift);

  setBalcony(Random::getBool());
  setLayout(layouts_[Random::getInt(0, layouts_.size() - 1)]);
}

std::ostream &Flat::print(std::ostream &out) const {
  return Flat::RealEstate::print(out) 
    << "Этаж: " << floor_ << '\n'
    << "Новостройка: " << (floor_ ? "Да" : "Нет")  << '\n'
    << "Балкон: " << (balcony_ ? "Есть" : "Нет") << '\n'
    << "Лифт: " << (lift_ ? "Есть" : "Нет") << '\n'  
    << "Планировка: " << layout_ << '\n';
}