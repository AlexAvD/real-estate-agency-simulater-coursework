#pragma once

#include <stack>
#include "Person.h"
#include "Client.h"
#include "Agency.h"
#include "Buyer.h"
#include "Seller.h"
#include "Report.h"

class Agency;
class Realtor : public Person {
  private:
    int experience_;
    float charisma_;
    bool sellerAndBuyerFound_;
    Date dateOfMeeting_;
    Date date_;
    Agency *agency_;
    Report *currentReport_;
    Client *currentClient_;
    Buyer *currentBuyer_;
    Seller *currentSeller_;
    std::stack<Seller*> sellers_;
    std::stack<Buyer*> buyer_;
    std::vector<Report> reports_;
    
  public: 
    Realtor();
    Realtor(Agency* agencry);
    Realtor(const Realtor &realtor);

    static Realtor generate();
    static void getRealtorsFromFile(const std::string &pathToFile, std::stack<Realtor> *dist);

    // setters

    void setExperience(int experience);
    void setExperience(const std::string &experience);
    void setCharisma(float charisma);
    void setCharisma(const std::string &charisma);
    void setDate(const Date &date);
    void setCurrentReport(const Report &report);
    void setCurrentClient(Client *buyer);
    void setCurrentBuyer(Buyer *buyer);
    void setCurrentSeller(Seller *seller);
    void setRandomProperties();
 
    // getters

    int getExperience() const;
    float getCharisma() const;
    Date getDate() const;
    Report getReports() const;
    Client *getCurrentClient() const;
    Buyer *getCurrentBuyer() const;
    Seller *getCurrentSeller() const;

    // others

    void addBuyer(Client *buyer);
    void addSeller(Client *seller);
    void addToReport(const Date &date, const std::string &action);

    void work();
    void searchClient();
    Buyer *searchBuyer();
    Seller *searchSeller();
    void arrangeMeeting();
    void meetingWithClient();
    void concludeContract();
    
    virtual std::ostream& print(std::ostream &out) const override;
};