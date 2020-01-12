#include "Client.h"


Client::Client() : Person() {
  realEstate_ = nullptr;
}

Client::Client(const Client &client) : Person(client) {
  realEstate_ = client.realEstate_;
}

Client::~Client() {

}

Client Client::generate() {
  Client client;

  client.setRandomProperties();

  return client;
}

// setters

void Client::setRealEstate(RealEstate *realEstate) {
  realEstate_ = realEstate;
}

void Client::setRandomProperties() {
  Client::Person::setRandomProperties();
}

// getters

RealEstate *Client::getRealEstate() const {
  return realEstate_;
}

// others

std::ostream &Client::print(std::ostream &out) const {
  Person::print(out);

  if (realEstate_) {
    out << realEstate_->getType() << ": " << realEstate_->getStreet() << "\n";
  }

  return out;
}
