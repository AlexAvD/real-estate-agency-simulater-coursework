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
    // площадь
    int area_;
    // год постройки 
    int buildYear_;
    // кол-во этажей
    int floors_;
    // кол-во комнат
    int rooms_;
    // тип продажи
    // -1 - нет, 0 - продажа, 1 - аренда
    int saleType_; 
    // есть ли мебель
    bool furniture_;
    // есть ли ремент
    bool repair_;
    // цена
    long price_;
    // улица
    std::string street_;
    // район
    std::string district_;
    // тип недвижимости
    std::string type_;
  
  protected:
    // вектор со всеми возможными типами
    static const std::vector<std::vector<std::string>> types_;
    // вектор хранящий пару с районом и вектор с улицами
    static const std::vector<std::pair<std::string, std::vector<std::string>>> districtsAndStreets_;

  public:
    RealEstate();
    RealEstate(const RealEstate &realEstate);
    ~RealEstate();

    // проверяет является ли преданный тип "typeOfRealEstate" квартирой
    static bool isFlat(const std::string &typeOfRealEstate);
    // проверяет является ли преданный тип "typeOfRealEstate" домом
    static bool isHouse(const std::string &typeOfRealEstate);

    // setters

    // устанавливает площадь
    void setArea(int area);
    // устанавливает год постройки
    void setBuildYear(int year);
    // устанавливает кол-во этажей
    void setFloors(int floors);
    // устанавливает кол-во комнат
    void setRooms(int rooms);
    // устанавливает тип продажи недвижимости
    void setSaleType(int saleType);
    // устанавливает мебель
    void setFurniture(bool furniture); 
    // устанавливает ремонт
    void setRepair(bool furniture);
    // устанавливает цену
    void setPrice(long price);
    // устанавливает улицу
    void setStreet(const std::string &street);
    // устанавливает район
    void setDistrict(const std::string &district);
    // устанавливает тип недвижимости
    void setType(const std::string &type);
    // устанавливает случайные свойства
    void setRandomProperties(int typeOfConstruction = -1);
    // принимает карту хранящую ключи, характеризующие свойства класса "RealEstate", и их значения
    // и возвращает карту в которой хранятся ключи, к которым не было найдено подходящих свойств
    virtual std::map<std::string, std::string> 
      setProperties(const std::map<std::string, std::string> &properties);

    // getters

    // возвращает площадь
    int getArea() const;
    // возвращает год постройки
    int getBuildYear() const;
    // возвращает кол-во этажей
    int getFloors() const;
    // возвращает кол-во комнат
    int getRooms() const;
    // возвращает тип продажи
    int getSaleType() const;
    // возвращает есть ли ремонт
    bool getRepair() const;
    // возвращает есть ли ремонт
    bool getFurniture() const;
    // возвращает цену
    long getPrice() const;
    // возвращает улицу
    std::string getStreet() const;
    // возвращает район
    std::string getDistrict() const;
    // возвращает тип недвижимости
    std::string getType() const;

    // виртуальные методы для класса Flat

    virtual int getFloor() const { return 0; }
    virtual bool getNewBuilding() const { return false; }
    virtual bool getBalcony() const { return false; }
    virtual bool getLift() const { return false; }
    virtual std::string getLayout() const { return ""; }

    // виртуальные методы для класса House

    virtual std::string getMaterial() const { return ""; }
    virtual int getPlotArea() const { return 0; }
    virtual bool getGarage() const { return false; }

    // operators

    RealEstate &operator=(const RealEstate &realEstate);

    // others

    virtual std::ostream &print(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const RealEstate &realEstate);
};