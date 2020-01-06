#include "Client.h"

const std::vector<std::string> Client::types_ {
  "Продавец",
  "Покупатель",
  "Арендодатель",
  "Арендатор"
};

Client::Client() : Person() {
  type_ = -1;
  realEstate_ = nullptr;
}

Client::Client(const Client &client) : Person(client) {
  type_ = -1;
  realEstate_ = nullptr;
}

// setters

void Client::setType(int type) {
  type_ = type;
}

void Client::setRealEstate(RealEstate *realEstate) {
  realEstate_ = realEstate;
}

void Client::setRandomProperties() {
  Client::Person::setRandomProperties();
}

// getters

int Client::getType() const {
  return type_;
}

RealEstate *Client::getRealEstate() const {
  return realEstate_;
}

// others

std::ostream &Client::print(std::ostream &out) const {
  Person::print(out);

  return out;
}

/* std::ostream& operator<<(std::ostream &out, const Client &client) {
  return client.print(out);
} */ 