#pragma once

#include <stack>
#include "Person.h"
#include "Client.h"
#include "Agency.h"
#include "Report.h"

class Agency;
class Realtor : public Person {
  private:
    int experience_;
    // максимум сколько может найти подходящей недвижимости риэлтор для покупателя
    int maxSuitableSellers_;
    // состоялние отрожающее, найдено ли максимальное количество подходящей недвижимости для покупателя
    bool isSuitableSellersFound_;
    // состояние отражающее ищет ли риэлтор покупателей
    bool isSearching_;
    // состояние отражающее начал ли риэлтор ознакамливать клиента со всеми подходящими вариантами недвижимости 
    bool isReviewing_;

    bool isSearchingSuitable_;

    bool isBuyerFound_;
    bool isSellerFound_;
    bool isClientFound_;
    
    bool didContractConclude_;

    long salary_;
    float charisma_;
    Date date_;
    Agency *agency_;
    Client currentBuyer_;
    Client currentSeller_;
    // владельцы с подходящей недвижимостью
    std::stack<Client> suitableSellers_;
    std::vector<Report> reports_;
    
  public: 
    Realtor();
    Realtor(const Realtor &realtor);

    static Realtor generate();
    static void getRealtorsFromFile(const std::string &pathToFile, std::stack<Realtor> *dist);
  
    // setters

    void setExperience(int experience);
    void setSalary(int salary);
    void setCharisma(float charisma);
    void setDate(const Date &date);
    void setReport(const Report &report);
    void setAgency(Agency *agency);
    void setRealEstate(RealEstate *realEstate);
    void setCurrentBuyer(const Client &client);
    void setCurrentSeller(const Client &client);
    void setRandomProperties();
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &proprerties) override;
 
    // getters
    int getChanceToFindBuyer() const;
    int getChanceToFindSeller() const;
    int getChanceToConludeRealtorContract() const;
    int getChanceThatBuyerMakePurchase() const;

    int getExperience() const;
    int getSalary() const;
    float getCharisma() const;
    Date getDate() const;
    Client getCurrentBuyer() const;
    Client getCurrentSeller() const;
    Client getSuitableSeller();
    std::vector<Report> getReports() const;

    // others

    bool isAgencyHasAppeals();

    void addSuitableSeller(const Client &seller);
    void addReport(const Date &date, RealEstate *realEstate, Client *buyer, long revenue);
    
    void work();
    void handleAppeals();
    void searchClients();
    void concludeRealtorContract();
    void concludeAssignmentContract();
    void handleSeller();
    void handleBuyer();
    void searchSuitableSellers();
    void reviewSuitableSellers();

    void clearSuitableSellers();
    
    virtual std::ostream& print(std::ostream &out) const override;
};