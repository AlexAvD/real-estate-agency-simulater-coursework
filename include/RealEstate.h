#pragma once

#include <iostream>
#include <sstream>
#include "Date.h"
#include "Person.h"

class Flat;
class RealEstate {
  private:
    int area_;
    int buildYear_;
    int floors_;
    int rooms_;
    bool furniture_;
    bool repair_;
    std::string street_;
    std::string district_;
    std::string type_;
    Person * owner_;
  
  protected:
    static std::vector<std::vector<std::string>> types_;
    static std::vector<std::pair<std::string, std::vector<std::string>>> districtsAndStreets_;

  public:
    RealEstate();
    RealEstate(const RealEstate &realEstate);

    // setters
    void setArea(int area);
    void setBuildYear(int year);
    void setFloors(int floors);
    void setRooms(int rooms);
    void setFurniture(bool furniture);
    void setRepair(bool furniture);
    void setStreet(std::string street);
    void setDistrict(std::string district);
    void setType(std::string type);
    void setOwner(Person *person);
    void setRandomProperties(int typeOfConstruction = -1);

    // getters
    int getArea() const;
    int getBuildYear() const;
    int getFloors() const;
    int getRooms() const;
    bool getRepair() const;
    bool getFurniture() const;
    std::string getStreet() const;
    std::string getDistrict() const;
    std::string getType() const;
    Person *getOwner() const;
    
    // others
    virtual std::ostream &print(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const RealEstate &realEstate);
};