#pragma once

#include <iostream>
#include <vector>
#include "RealEstate.h"

class Flat : public RealEstate {
  private:
    // вектор хранящий все возможные планировки
    static const std::vector<std::string> layouts_;
    // этаж
    int floor_;
    // первичка или вторичка
    bool newBuilding_;
    // есть ли балкон
    bool balcony_;
    // есть ли лифт
    bool lift_;
    // планировка
    std::string layout_;

  public:
    Flat();
    Flat(const Flat &flat);

    // генерирует объект класса Flat со случайными свойствами
    static Flat generate();
    // считывает файл хранящий данные квартир и на основе этих данных создает объект "Flat" и добавляет его в стэк "dist"
    static void getFlatsFromFile(const std::string &pathToFile, std::stack<Flat> *dist);
   
    // settesr

    // устанавливает этаж
    void setFloor(int floor);
    // устанавливает год постройки
    void setNewBuilding(bool newBuilding);
    // устанавливает есть ли балкон
    void setBalcony(bool balcony);
    // устанавливает есть ли лифе
    void setLift(bool lift);
    // устанавливает планировку
    void setLayout(std::string layout);
    // устанавливает случайные свойства
    void setRandomProperties();
    // принимает карту хранящую ключи, характеризующие свойства класса "Flat", и их значения
    // и возвращает карту в которой хранятся ключи, к которым не было найдено подходящих свойств
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &properties) override;

    // getters

    // возвращает этаж
    virtual int getFloor() const override;
    // возвращает первичка ли это или вторичка
    virtual bool getNewBuilding() const override;
    // возвращает есть ли балкон
    virtual bool getBalcony() const override;
    // возвращает есть ли лифт
    virtual bool getLift() const override;
    // возвращает планировку
    virtual std::string getLayout() const override;

    // others
    
    virtual std::ostream &print(std::ostream &out) const override;

};