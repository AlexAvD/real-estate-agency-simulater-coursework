#include "Buyer.h"
 
 
Buyer::Buyer() : Client() {

}

Buyer::Buyer(const Buyer &buyer) : Client(buyer) {

}

void Buyer::setRandomProperties() {
  Buyer::Client::setRandomProperties();

  int type = Random::getInt(2, 3);
  
  setType(type);

  if (type == 2) {
    setMoney(Random::getInt(2000000, 5000000));
  }
}

Buyer Buyer::generate() {
  Buyer buyer;

  buyer.setRandomProperties();

  return buyer;
}

std::ostream& Buyer::print(std::ostream &out) const {
  out << "=== Buyer ===" << '\n';

  return Client::print(out);
}
