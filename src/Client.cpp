#include "Client.h"

Client::Client() : Person() {
  realEstate_ = nullptr;
}

Client::Client(const Person &person) : Person(person) {
  realEstate_ = nullptr;
}

Client Client::generate() {
  return Client(Client::Person::generate());
}

Client::Client(const Person &person, RealEstate *realEstate) : Person(person) {
  realEstate_ = realEstate;
}

void Client::setRealEstate(RealEstate *realEstate) {
  realEstate_ = realEstate;
}

RealEstate * Client::getRealEstate() const {
  return realEstate_;
}

std::ostream& Client::print(std::ostream &out) const {
  out << "=== CLIENT ===" << '\n';

  return Person::print(out);
}

/* std::ostream& operator<<(std::ostream &out, const Client &client) {
  return client.print(out);
} */ 