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
    int maxSellers_;
    bool allSellersFound_;
    // состояние отражающее ищет ли риэлтор покупателя
    bool isSearching_;
    bool isViewing_;
    int chanceToConcludeContract_;
    bool contractConcluded_;
    long salary_;
    float charisma_;
    Date date_;
    Agency *agency_;
    Client *buyer_;
    std::stack<Client*> sellers_;
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
    void setBuyer(Client *client);
    void setRandomProperties();
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &proprerties) override;
 
    // getters
    int getExperience() const;
    int getSalary() const;
    float getCharisma() const;
    Date getDate() const;
    Client *getBuyer() const;
    Client *getSeller() const;
    std::vector<Report> getReports() const;

    // others

    void addSeller(Client *seller);
    void addBuyer(Client *buyer);
    void addReport(const Date &date, RealEstate *realEstate, Client *buyer, long revenue);

    void work();
    Client *searchBuyer();
    Client *searchSeller();
    
    virtual std::ostream& print(std::ostream &out) const override;
};