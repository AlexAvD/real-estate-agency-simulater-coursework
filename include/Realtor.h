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
    float charisma_;
    Date date_;
    Agency *agency_;
    Client *buyer_;
    RealEstate *realEstate_;
    std::vector<Report> reports_;
    
  public: 
    Realtor();
    Realtor(Agency* agencry);
    Realtor(const Realtor &realtor);

    static Realtor generate();
    static void getRealtorsFromFile(const std::string &pathToFile, std::stack<Realtor> *dist);

    // setters

    void setExperience(int experience);
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
    float getCharisma() const;
    Date getDate() const;
    RealEstate *getRealEstate() const;
    std::vector<Report> getReports() const;
    Client *getBuyer() const;

    // others


    void addBuyer(Client *buyer);
    void addReport(const Date &date, RealEstate *realEstate, Client *buyer, long revenue);

    void work();
    void searchClient();
    Client *searchBuyer();
    
    virtual std::ostream& print(std::ostream &out) const override;
};