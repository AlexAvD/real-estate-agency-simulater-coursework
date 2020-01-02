#include "Realtor.h"

Realtor::Realtor() {
  buyer_ = seller_ = nullptr;
}

Realtor::Realtor(Agency* agency) {
  buyer_ = seller_ = nullptr;
  agency_ = agency;
}

void Realtor::setBuyer(Client* buyer) {
  buyer_ = buyer;
}

void Realtor::setSeller(Client* seller) {
  seller_ = seller;
}

Client* Realtor::searchClient() {
  int percent = asymp(experience_, 20, 50, 2);

  if (chance(percent)) {
    
  }

  return nullptr;
}

