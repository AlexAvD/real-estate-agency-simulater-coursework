#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include "Date.h"
#include "Realtor.h"
#include "Flat.h"
#include "House.h"
#include "Report.h"

class Realtor;
class Agency {
  private:  
    int workDays_;
    int workHours_;
    long revenue_;
    float taxRate_;
    float saleCommision_;
    float rentCommision_;
    Date date_;
    std::vector<Realtor> realtors_;
    std::stack<Flat> *flats_;
    std::stack<House> *houses_;
    std::vector<RealEstate*> soldRealEstates_;
    std::stack<Flat> flatsForSale_;
    std::stack<House> housesForSale_;
    std::stack<Client> buyers_;

  public:
    Agency();
    Agency(
      std::stack<Realtor> *realtors, 
      std::stack<Flat> *flats, 
      std::stack<House> *houses
    );

    // settesr

    void setRealtors(std::stack<Realtor> *realtors);
    void setFlats(std::stack<Flat> *flats);
    void setHouses(std::stack<House> *houses);

    // getters

    long getRevenue() const;
    float getSaleCommision() const;
    float getRentCommision() const;
    Date getDate() const;
    Flat getFlat();
    House getHouse();
    RealEstate *getRealEstate();

    std::vector<Realtor> *getRealtors();
    std::vector<RealEstate*> *getSoldRealEstates();

    std::stack<Flat> *getFlats();
    std::stack<House> *getHouses();
    std::stack<Client> *getBuyers();
    std::stack<House> *getHousesForSale();
    std::stack<Flat> *getFlatsForSale();

    // others

    void simulate();
    void writeReport(const std::string pathToFile);
    void addRevenue(int revenue);
    void addSoldRealEstate(RealEstate *realEstate);
    Client *addBuyer(const Client &buyer);
    Flat *addFlatForSale(const Flat &flat);
    House *addHouseForSale(const House &house);

    
};