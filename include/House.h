#pragma once

#include "RealEstate.h"

class House : public RealEstate {
  private:
    static const std::vector<std::string> wallMaterials_;
    
    int plotArea_;
    bool garage_;
    std::string wallMaterial_;

  public:
    House();
    House(const House &house);

    static House generate();

    // setters

    void setGarage(bool garage);
    void setPlotArea(int plotArea);
    void setWallMaterial(const std::string &wallMaterial);
    void setRandomProperties();

    // getters
    
    int getPlotArea() const;
    bool getGarage() const; 
    std::string getWallMaterial() const;

    // others

    virtual std::ostream &print(std::ostream &out) const override;
};

