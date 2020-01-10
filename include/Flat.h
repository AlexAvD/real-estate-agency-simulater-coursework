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

    static Flat generate();
    static void getFlatsFromFile(const std::string &pathToFile, std::stack<Flat> *dist);
   
    // settesr

    void setFloor(int floor);
    void setNewBuilding(bool newBuilding);
    void setBalcony(bool balcony);
    void setLift(bool lift);
    void setLayout(std::string layout);
    void setRandomProperties();
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &proprerties) override;

    // getters

    virtual int getFloor() const override;
    virtual bool getNewBuilding() const override;
    virtual bool getBalcony() const override;
    virtual bool getLift() const override;
    virtual std::string getLayout() const override;

    // others
    
    virtual std::ostream &print(std::ostream &out) const override;

};