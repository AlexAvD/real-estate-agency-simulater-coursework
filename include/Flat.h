#pragma once

#include <iostream>
#include <vector>
#include "RealEstate.h"

class Flat : public RealEstate {
  private:
    static const std::vector<std::string> layouts_;

    int floor_;
    bool newBuilding_;
    bool balcony_;
    bool lift_;
    std::string layout_;

  public:
    Flat();
    Flat(const Flat &flat);
   
    // settesr
    void setFloor(int floor);
    void setNewBuilding(bool newBuilding);
    void setBalcony(bool balcony);
    void setLift(bool lift);
    void setLayout(std::string layout);

    // getters
    int getFloor() const;
    bool getNewBuilding() const;
    bool getBalcony() const;
    bool getLift() const;
    std::string getLayout() const;

    // others
    virtual Flat &setRandomProperties();
    virtual std::ostream &print(std::ostream &out) const override;

};