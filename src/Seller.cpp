#include "Seller.h"

Seller::Seller() : Client() {

}

Seller::Seller(const Person &person) : Client(person) {

}

Seller::Seller(const Person &person, RealEstate *realEstate) : Client(person, realEstate) {

}

Seller Seller::generate() {
  return Seller(Seller::Client::Person::generate());
}

std::ostream& Seller::print(std::ostream &out) const {

  out << "=== SELLER ===" << '\n';

  return Client::Person::print(out);
}
