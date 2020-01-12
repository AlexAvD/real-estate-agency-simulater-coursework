#pragma once

#include <iostream>
#include <sstream>
#include <stack>
#include "Date.h"
#include "Client.h"

class Flat;
class House;
class Client;
class RealEstate {
  private:
    int area_;
    int buildYear_;
    int floors_;
    int rooms_;
    int saleType_; // -1 - no sale, 0 - sale, 1 - rent
    bool furniture_;
    bool repair_;
    long price_;
    std::string street_;
    std::string district_;
    std::string type_;
  
  protected:
    static const std::vector<std::vector<std::string>> types_;
    static const std::vector<std::pair<std::string, std::vector<std::string>>> districtsAndStreets_;

  public:
    RealEstate();
    RealEstate(const RealEstate &realEstate);
    ~RealEstate();

    static bool isFlat(const std::string &typeOfRealEstate);
    static bool isHouse(const std::string &typeOfRealEstate);

    // setters
    void setArea(int area);
    void setBuildYear(int year);
    void setFloors(int floors);
    void setRooms(int rooms);
    void setSaleType(int saleType);
    void setFurniture(bool furniture); 
    void setRepair(bool furniture);
    void setPrice(long price);
    void setStreet(const std::string &street);
    void setDistrict(const std::string &district);
    void setType(const std::string &type);
    void setRandomProperties(int typeOfConstruction = -1);

    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &proprerties);

    // getters
    int getArea() const;
    int getBuildYear() const;
    int getFloors() const;
    int getRooms() const;
    int getSaleType() const;
    bool getRepair() const;
    bool getFurniture() const;
    long getPrice() const;
    std::string getStreet() const;
    std::string getDistrict() const;
    std::string getType() const;

    // Flat
    virtual int getFloor() const { return 0; }
    virtual bool getNewBuilding() const { return false; }
    virtual bool getBalcony() const { return false; }
    virtual bool getLift() const { return false; }
    virtual std::string getLayout() const { return ""; }

    // House
    virtual std::string getMaterial() const { return ""; }
    virtual int getPlotArea() const { return 0; }
    virtual bool getGarage() const { return false; }

    // operators

    RealEstate &operator=(const RealEstate &realEstate);

    // others

    virtual std::ostream &print(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const RealEstate &realEstate);
};