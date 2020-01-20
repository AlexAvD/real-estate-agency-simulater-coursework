#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include "Date.h"
#include "Realtor.h"
#include "Flat.h"
#include "House.h"
#include "RealEstate.h"

class Realtor;
class Agency {
  private:  
    // количество дней для симуляции
    int workDays_;
    // кол-во рабочих часов
    int workHours_;
    // шанс того, что покупатель свяжется с агентством
    int chanceBuyerWillAppeal_;
    // шанс того, что продавец свяжется с агентством
    int chanceSellerWillAppeal_;
    // кол-во проданной недвижимости
    int nSold_;
    // кол-во арендованной недвижимости
    int nRented_;
    // доходы фирмы
    long revenue_;
    // дата
    Date date_;
    // ндс фирмы
    float taxRate_;
    // комиссия риэлтора - процент с продажи который берет риэлтор, как доход фирмы
    float saleCommision_;
    // комиссия риэлтора - процент с аренды который берет риэлтор, как доход фирмы
    float rentCommision_;
    // процент комисии, которую получает риэлтор после удачной следки
    float realtorCommision_;
    // список со всеми риэлторами
    std::list<Realtor> realtors_;
    // список со всеми квартирами
    std::list<Flat> flats_;
    // список со всеми домами
    std::list<House> houses_;
    // вектор со всеми доступными для риэлтора продавцами
    std::vector<Client> availableSellers_;
    // покупатели которые обратились в агентство
    std::stack<Client> appealedBuyers_;
    // продавцы которые обратились в агентство 
    std::stack<Client> appealedSellers_;
    // клиенты которые приобрели недвижимость
    std::stack<Client> buyersPurchased_;
    // карта в которой будет отражаться как часто покупают/арендуют тот или иной тип недвижимости
    std::map<std::string, int> popularRealEstates_;

  public:
    Agency();
    Agency(
      std::stack<Realtor> *realtors, 
      std::stack<Flat> *flats, 
      std::stack<House> *houses
    );

    // setters

    // переносит всех риэлоторв из стэка "realtors" в список "realtors_"
    void setRealtors(std::stack<Realtor> *realtors);
    // переносит все квартиры из стэка "flats" в список "flats_"
    void setFlats(std::stack<Flat> *flats);
    // переносит все дома из стэка "houses" в список "houses_"
    void setHouses(std::stack<House> *houses);
    // создает продавцов/арендодаторов с недвижимостью, которая берется из списков "flats_" и "houses_", и заполняет вектор "availableSellers_"
    void setAvailableSellers();

    // getters

    // возвращает доходы фирмы
    long getRevenue() const;
    // возвращает процент с продажи который берет риэлтор, как доход фирмы
    float getSaleCommision() const;
    // возвращает процент с аренды который берет риэлтор, как доход фирмы
    float getRentCommision() const;
    // возвращает процент комисии, которую получает риэлтор после удачной следки
    float getRealtorCommision() const;
    // возвращает дату
    Date getDate() const;

    // возвращает список с риэлторами
    std::list<Realtor>  &getRealtors();
    // возвращает список с квартирами
    std::list<Flat>     &getFlats();
    // возвращает список с домами
    std::list<House>    &getHouses();

    // возвращает вектор хранящий всех доступных продавцов для риэлтора
    std::vector<Client> &getAvailableSellers();
    // возвращает стэк хранящий всех покупателей, которые обратились в агентство 
    std::stack<Client> &getAppealedBuyers();
    // возвращает стэк хранящий всех продавцов, которые обратились в агентство 
    std::stack<Client> &getAppealedSellers();

    // достает из стэка "availableSellers_" продовца/арендодатора
    Client getAvailableSeller();
    // достает из стэка "appealedBuyers_" продовца/арендодатора, который обратился в агентство
    Client getAppealedSeller();
    // достает из стэка "appealedBuyers_" покупателя/арендатора, который обратился в агентство
    Client getAppealedBuyer();

    // others

    // проверяет были ли обращения фирмы
    bool hasAppeals() const;
    // проверяет обратился ли в фирму покупатель
    bool didBuyerAppeal() const;
    // проверяет обратился ли в фирму продавец
    bool didSellerAppeal() const;

    // добавляет продовца в стэк с продовцами, которые обратились в агентство
    void addAppealedSeller(const Client &seller);
    // добавляет покупателя в стэк с покупателями, которые обратились в агентство
    void addAppealedBuyer(const Client &buyer);
    // добавляет продавца в вэктор с доступными, для риэлтора, продовцами
    void addAvailableSeller(const Client &availableSeller);
    // добавляет клиента в стэк со всеми клиентами, которые купили/арендовали недвижимость
    // и возвращает ссылку на этого клиента
    Client *addBuyersPurchased(const Client &buyerPurchased);

    // добавляет квартиру в список со всеми квартирами
    Flat *addFlat(const Flat &flat);
    // добавляет дом в список со всеми домами
    House *addHouse(const House &house);
    
    // генерируте и возвращает продовца продовца 
    Client generateSeller();
    // генерируте и возвращает продовца покупателя
    Client generateBuyer();
    // генерируте и добавляет покупателя в стэк с покупателями, которые обратились в агентство
    void generateAndAddBuyer();
    // генерируте продовца/арендатора с недвижимостью и добавляет его в стэк с продовцами/арендаторами, 
    // которые обратились в агентство
    void generateAndAddSeller();
    // функция генерирует продовца/арендодатора или покупателя/арендателя и добавляет в стэк с обращениями
    void generateAndAddClient();

    // симулирует работу фирмы
    void simulate();
    // создает файл с результатами симуляции
    void writeReport(const std::string pathToFile);
};