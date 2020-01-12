#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include "Date.h"
#include "Realtor.h"
#include "Flat.h"
#include "House.h"
#include "Report.h"
#include "RealEstate.h"

class Realtor;
class Agency {
  private:  
    int workDays_;
    int workHours_;
    // шанс того, что покупатель свяжется с агенством
    int chanceBuyerWillContact_;
    // шанс того, что продавец свяжется с агенством
    int chanceSellerWillContact_;
    long revenue_;
    Date date_;
    // ндс фирмы
    float taxRate_;
    // комисия риэлтора - процент с продажи который берет риэлтор, как доход фирмы
    float saleCommision_;
    // комисия риэлтора - процент с аренды который берет риэлтор, как доход фирмы
    float rentCommision_;
    // процент комисии, которую должне риэлтор фирме 
    float salaryRate_;
    // хранит всех риэлторов 
    std::vector<Realtor> realtors_;
    // хранит все квартиры
    std::vector<Flat> flats_;
    // хранит все дома 
    std::vector<House> houses_;
    // хранит всех клиентов 
    std::vector<Client> clients_;
    // хранит всех доступных продвоцов с недвижимостью для риэлторов
    std::stack<Client*> availableSellers_;
    // покупатели которые обратились в агенство 
    std::stack<Client*> buyers_;
    // продавцы которые обратились в агенство 
    std::stack<Client*> sellers_;

  public:
    Agency();
    Agency(
      std::stack<Realtor> *realtors, 
      std::stack<Flat> *flats, 
      std::stack<House> *houses
    );

    // setters

    void setRealtors(std::stack<Realtor> *realtors);
    void setFlats(std::stack<Flat> *flats);
    void setHouses(std::stack<House> *houses);
    void setClients();
    void setAvailableSellers();

    // getters

    long getRevenue() const;
    float getSaleCommision() const;
    float getRentCommision() const;
    Date getDate() const;

    std::vector<Realtor>  &getRealtors();
    std::vector<Flat>     &getFlats();
    std::vector<House>    &getHouses();
    std::vector<Client>   &getClients();

    std::stack<Client*> &getAvailableSellers();
    std::stack<Client*> &getBuyers();
    std::stack<Client*> &getSellers();

    Client *getAvailableSeller();
    Client *getSeller();
    Client *getBuyer();

    // others
    Client *addSeller(Client *seller);
    Client *addBuyer(Client *buyer);
    Client *addClient(const Client &client);
    
    Flat *addFlat(const Flat &flat);
    House *addHouse(const House &house);
    Client *addAvailableSeller(Client *availableSeller);

    
    Client *generateSeller();
    Client *generateBuyer();
    void generateAndAddBuyer();
    void generateAndAddSeller();
     
    /* функция имитирует обращения клиентов в агенство недвижимости */
    void generateAndAddClient();

    void simulate();
    void writeReport(const std::string pathToFile);
    void addRevenue(int revenue);
    
};