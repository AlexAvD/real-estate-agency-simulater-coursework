#include "House.h"

const std::vector<std::string> House::wallMaterials_ = {
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
  wallMaterial_ = "";
}

House::House(const House &house) : RealEstate(house) {
  plotArea_ = 0;
  garage_ = false;
  wallMaterial_ = "";
}

House House::generate() {
  House house;

  house.setRandomProperties();

  return house;
}

// setters

void House::setGarage(bool garage) {
  garage_ = garage;
}

void House::setWallMaterial(const std::string &wallMaterial) {
  wallMaterial_ = wallMaterial;
}

void House::setPlotArea(int plotArea) {
  plotArea_ = plotArea;
}

void House::setRandomProperties() {
  House::RealEstate::setRandomProperties(1);

  wallMaterial_ = wallMaterials_[Random::getInt(0, wallMaterials_.size() - 1)];
  garage_ = Random::getBool();
  plotArea_ = Random::getInt(100, 500);
}

// getters

int House::getPlotArea() const {
  return plotArea_;
}

bool House::getGarage() const {
  return garage_;
}

std::string House::getWallMaterial() const {
  return wallMaterial_;
}

// others

std::ostream &House::print(std::ostream &out) const {
  House::RealEstate::print(out);
  out 
    << "Материал стен: " << wallMaterial_ << "\n"
    << "Площадь участка: " << plotArea_ << " м^2\n" 
    << "Гараж: " << ((garage_) ? "Есть" : "Нет") << "\n";

  return out;
}
