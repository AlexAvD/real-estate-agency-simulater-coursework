#pragma once

#include "RealEstate.h"

class House : public RealEstate {
  private:
    static const std::vector<std::string> materials_;
    
    int plotArea_;
    bool garage_;
    std::string material_;

  public:
    House();
    House(const House &house);

    static House generate();
    static void getHousesFromFile(const std::string &pathToFile, std::stack<House> *dist);


    // setters

    void setGarage(bool garage);
    void setPlotArea(int plotArea);
    void setMaterial(const std::string &wallMaterial);
    void setRandomProperties();
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &proprerties) override;

    // getters
    
    virtual int getPlotArea() const override;
    virtual bool getGarage() const override; 
    virtual std::string getMaterial() const override;

    // others

    virtual std::ostream &print(std::ostream &out) const override;
};

