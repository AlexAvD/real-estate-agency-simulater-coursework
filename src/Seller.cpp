#include "Seller.h"

Seller::Seller() : Client() {

}

Seller::Seller(const Seller &seller) : Client(seller) {

}

void Seller::setRandomProperties() {
  Seller::Client::setRandomProperties();

  setType(Random::getInt(0, 1));
  setMoney(Random::getInt(100000, 500000));
}

Seller Seller::generate() {
  Seller seller;

  seller.setRandomProperties();

  return seller;
}

std::ostream& Seller::print(std::ostream &out) const {
  out << "=== SELLER ===" << '\n';

  return Client::print(out);
}
