#pragma once

#include "RealEstate.h"

class House : public RealEstate {
  private:
    // вектор хранящий все возможные материалы
    static const std::vector<std::string> materials_;
    // площадь участка
    int plotArea_;
    // есть ли гараж
    bool garage_;
    // материал
    std::string material_;

  public:
    House();
    House(const House &house);

    // генерирует объект класса House со случайными свойствами
    static House generate();
    // считывает файл хранящий данные домов и на основе этих данных создает объект "House" и добавляет его в стэк "dist"
    static void getHousesFromFile(const std::string &pathToFile, std::stack<House> *dist);

    // setters

    // устанавливает гараж
    void setGarage(bool garage);
    // устанавливает площадь участка
    void setPlotArea(int plotArea);
    // устанавливает материал
    void setMaterial(const std::string &wallMaterial);
    // устанавливает случайные свойства
    void setRandomProperties();
    // принимает карту хранящую ключи, характеризующие свойства класса "Flat", и их значения
    // и возвращает карту в которой хранятся ключи, к которым не было найдено подходящих свойств
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &properties) override;

    // getters
    
    // возвращает площадь участка
    virtual int getPlotArea() const override;
    // возвращает есть ли гараж
    virtual bool getGarage() const override; 
    // возвращает материал
    virtual std::string getMaterial() const override;

    // others

    virtual std::ostream &print(std::ostream &out) const override;
};

