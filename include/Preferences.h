#pragma once

#include <iostream>
#include <vector>

class Preferences {
  private:
    std::vector<std::string> infrastructure_;
    std::string type_;
    std::string wallMaterial_;
    std::string district_;
    int area_;
    int nRooms_;
    int nFloors_;
    int floor_;
    long price_;

  public:
    Preferences();
    Preferences(
      std::string type, long price, int area, int nRooms, int nFloors, int floor = 0,
      std::string district = "", std::string wallMaterail = "", 
      std::vector<std::string> infrastructure = {}
    );
    
    // setters
    void setArea(int area);
    void setNRooms(int nRooms);
    void setFloor(int floor);
    void setNFloors(int floor);
    void setPrice(long price);
    void setType(std::string type);
    void setDistrict(const std::string & district);
    void setInfrastructure(std::vector<std::string> infrastructure);
 
    // getters
    int getArea() const;
    int getNRooms() const;
    int getFloor() const;
    int getNFloors() const;
    long getPrice() const;
    std::string getType() const;
    std::string getDistrict() const;
    std::vector<std::string> getInfrastructure() const;

};