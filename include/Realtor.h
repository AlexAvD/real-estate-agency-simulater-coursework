#pragma once

#include <stack>
#include <sstream>
#include "Person.h"
#include "Client.h"
#include "Agency.h"

class Agency;
class Realtor : public Person {
  private:
    // опыт в годах
    int experience_;
    // зарплата
    long salary_;
    // харизма 
    float charisma_;
    // заработано с продажи/аренды недвижимостей
    long earnings_;
    // найдено ли максимальное количество подходящей недвижимости для покупателя
    bool isSuitableSellersFound_;
    // ищет ли риэлтор покупателей
    bool isSearching_;
    // начал ли риэлтор ознакамливать клиента со всеми подходящими вариантами недвижимости 
    bool isReviewing_;
    // идет ли поиск подходящих вариантов
    bool isSearchingSuitables_;
    // найден ли покупатель
    bool isBuyerFound_;
    // найден ли продовец
    bool isSellerFound_;
    // найден ли клиент, или продовец, или покупатель
    bool isClientFound_;
    // заключен ли контракт с риэлтором
    bool didRealtorContractConclude_;
    // дата
    Date date_;
    // агентство в котором работает риэлтор 
    Agency *agency_;
    // покупатель с которым работает риэлтор в данный момент
    Client currentBuyer_;
    // продавец с которым работает риэлтор в данный момент
    Client currentSeller_;
    // поток в который будут записываться события, которые происходили с риэлтором
    std::stringstream log_;
    // вектор со всеми событиями 
    std::vector<std::string> logs_;
    // владельцы с подходящей недвижимостью
    std::stack<Client> suitableSellers_;
    
  public: 
    Realtor();
    Realtor(const Realtor &realtor);

    // генерирует случайного риэлтора со случайными свойствами
    static Realtor generate();
    // считывает файл с данными на риэлторов и на основе этих данных создает объект "Realtor" и добавляет его в стэк "dist"
    static void getRealtorsFromFile(const std::string &pathToFile, std::stack<Realtor> *dist);
  
    // setters

    // устанавливает опыт
    void setExperience(int experience);
    // устанавливает зарплату
    void setSalary(int salary);
    // устанавливает харизму
    void setCharisma(float charisma);
    // устанавливает дату
    void setDate(const Date &date);
    // устанавливает агентство
    void setAgency(Agency *agency);
    // устанавливает текущего покупателя
    void setCurrentBuyer(const Client &client);
    // устанавливает текущего продовца
    void setCurrentSeller(const Client &client);
    // устанавливает случайные свойства
    void setRandomProperties();
    // принимает карту хранящую ключи, характеризующие свойства класса "Realtor", и их значения
    // и возвращает карту в которой хранятся ключи, к которым не было найдено подходящих свойств
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &properties) override;
 
    // getters

    // возвращает шанс того, что покупатель будет найден
    int getChanceToFindBuyer() const;
    // возвращает шанс того, что продавец будет найден
    int getChanceToFindSeller() const;
    // возвращает шанс того, что риэлторский контракт будет заключен
    int getChanceToConludeRealtorContract() const;
    // возвращает шанс того, что покупатель захочет приобрести недвижимость
    int getChanceThatBuyerMakePurchase() const;
    // возвращает максимальное число походящих продавцов, которых может найти риэлтор
    int getMaxSuitableSellers() const;
    // возвращает опыт
    int getExperience() const;
    // возвращает зарплату
    int getSalary() const;
    // возвращает доходы с продажи/аренды недвижимостей
    long getEearnings() const;
    // возвращает харизму
    float getCharisma() const;
    // возвращает дату
    Date getDate() const;
    // возвращает текущего покупателя
    Client getCurrentBuyer() const;
    // возвращает текущего продовца
    Client getCurrentSeller() const;
    // достает из стэка "suitableSellers_" продовца
    Client getSuitableSeller();
    // возвращает вектор со всеми событиями 
    std::vector<std::string> &getLogs();

    // others

    // считает прибыль и скалывает ее с общей прибылью, на основе недвижимости которую приобрел покупатель "buyerPurchased"
    void calcAndAddEarnings(Client *buyerPurchased);
    // проверяет были ли обращения в агентство
    bool isAgencyHasAppeals();
    // добавляет продовца в стэк с подходящими продовцами
    void addSuitableSeller(const Client &seller);
    // очищает стэк с подходящими продовцами, добавляя их в стэк "availableSellers_" агентства
    void clearSuitableSellers();
    // записывает событие в поток "log_"
    void log();
    // функция где будет описываться логика работы риэлтора
    void work();
    // функция где будет описываться логика обработки обращений клиентов в агенство
    void handleAppeals();
    // функция где будет описываться логика поиска клиентов
    void searchClients();
    // функция где будет описываться логика заключения риэлторсокого контракта
    void concludeRealtorContract();
    // функция где будет описываться логика заключения контракта приобретения недвижимости
    void concludeAssignmentContract();
    // функция где будет описываться логика обработки продавца 
    void handleSeller();
    // функция где будет описываться логика обработки покупателя
    void handleBuyer();
    // функция где будет описываться логика поиска походящих продавцов
    void searchSuitableSellers();
    // функция где будет описываться логика обзора походящей недвижимости
    void reviewSuitableSellers();
    
    virtual std::ostream& print(std::ostream &out) const override;
};