#pragma once

#include <stack>
#include "Person.h"
#include "Client.h"
#include "Agency.h"
#include "Buyer.h"
#include "Seller.h"

class Agency;
class Realtor : public Person {
  private:
    int experience_;
    float charisma_;
    Agency *agency_;
    Client *currentClient_;
    Buyer *currentBuyer_;
    Seller *currentSeller_;
    std::stack<Seller*> sellers_;
    std::stack<Buyer*> buyer_;

  public: 
    Realtor();
    Realtor(Agency* agencry);
    Realtor(const Realtor &realtor);

    static Realtor generate();

    // setters
    void setExperience(int experience);
    void setCharisma(float charisma);
    void setCurrentClient(Client *buyer);
    void setCurrentBuyer(Buyer *buyer);
    void setCurrentSeller(Seller *seller);
    void setRandomProperties();
 
    // getters
    int getExperience() const;
    float getCharisma() const;
    Client *getCurrentClient() const;
    Buyer *getCurrentBuyer() const;
    Seller *getCurrentSeller() const;

    // others
    void addBuyer(Client *buyer);
    void addSeller(Client *seller);

    void work();
    void searchClient();
    Buyer *searchBuyer();
    Seller *searchSeller();
    void concludeContract();
    
    virtual std::ostream& print(std::ostream &out) const override;
};