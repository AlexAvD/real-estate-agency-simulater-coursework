#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Date.h"
#include "Client.h"
#include "RealEstate.h"

class Report {
  private:
    Date date_;
    Client *buyer_;
    RealEstate *realEstate_;
    long revenue_;

  public:
    Report();
    Report(const Date &date, RealEstate *realEstate, Client *buyer, long revenue);
    Report(const Report &report);

    // setters

    // getters
    RealEstate *getRealEstate() const;
    long getRevenue() const;

    // others
    template <class T>
    friend T &operator<<(T &out, const Report &report) {
      out << "                 ╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼ "<< report.date_ << " ╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼\n\n"
          << "Недвижимость типа \"" << report.realEstate_->getType()
          << "\" со следующими характеристиками:\n\n" 
          << li << "Район: " << report.realEstate_->getDistrict() << '\n'
          << li << "Улица: " <<  report.realEstate_->getStreet() << '\n'
          << li << "Год постройки: " << report.realEstate_->getBuildYear() << '\n'
          << li << "Площадь: " << report.realEstate_->getArea() << " м^2" << '\n'
          << li << "Кол-во комнат: " << report.realEstate_->getRooms() << '\n'
          << li << "Ремонт: " << (report.realEstate_->getRepair() ? "Есть" : "Нет")  << '\n'
          << li << "Мебель: " << (report.realEstate_->getFurniture() ? "Есть" : "Нет") << '\n'
          << li << "Этажность: " << report.realEstate_->getFloors() << '\n';

      if (report.realEstate_->getSaleType() == 1) {
        out << li << "Этаж: " << report.realEstate_->getFloor() << '\n'
            << li << "Новостройка: " << (report.realEstate_->getNewBuilding() ? "Да" : "Нет")  << '\n'
            << li << "Балкон: " << (report.realEstate_->getBalcony() ? "Есть" : "Нет") << '\n'
            << li << "Лифт: " << (report.realEstate_->getLift() ? "Есть" : "Нет") << '\n'  
            << li << "Планировка: " << report.realEstate_->getLayout() << '\n';
      } else  if (report.realEstate_->getSaleType() == 0) {
        out << li << "Материал: " << report.realEstate_->getMaterial() << '\n'
            << li << "Площадь участва: " << report.realEstate_->getPlotArea() << " м^2" << '\n'
            << li << "Гараж: " << (report.realEstate_->getGarage() ? "Есть" : "Нет") << '\n';
      }

      out << li << "Тип продажи: " << (report.realEstate_->getSaleType() == 0 ? "Продажа" : "Аренда") << '\n'
          << li << "Цена: " << report.realEstate_->getPrice() << '\n';

      out << "\nБыла " << ((report.realEstate_->getSaleType() == 0) ? "продана" : "сдана в аренду")
          << " клиенту:\n\n"
          << li << "ФИО: " << report.buyer_->getFullName() << '\n'
          << li << "Возраст: " << report.buyer_->getAge() << '\n'
          << li << "Паспортные данные: " << report.buyer_->getPassportData() << '\n'
          << "\nЗа " << report.realEstate_->getPrice() << ". "
          << "Доход фирмы составил: " << report.revenue_ << " руб.\n\n";
          // << "╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼╼\n";

      return out;
    }


    


};