#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include "Random.h"


double asymp(double num, double min, double max, double growRate = 1);

// локализация
void setRus();

// текст
bool isBlank(const std::string & str);
std::vector<std::string> tokenize(const std::string & str, char separator);
std::string normalizeLine(const std::string & str);
std::string concat(const std::vector<std::string> & strings, char ch);
std::string trim(const std::string & str);

bool chance(int percent = 100);

// векторы

// функция возвращает количество совпадающих эелементов вектора "elements" в векторе "src"
int countEqualElements(const std::vector<std::string> & src, const std::vector<std::string> & elements);

// файлы

// функция считывает файл и возвращает vector
std::vector<std::map<std::string, std::string>> readFile(const std::string & fileName);

// вывод всех данных контейнреа vector
template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> & v) {
  for (size_t i = 0, size = v.size(); i < size; i++) {
    out << v[i] << '\n';
  }

  return out;
}

// вывод всех данных контейнреа map
template <class T, class L> 
std::ostream& operator<<(std::ostream &out, const std::map<T, L> & m) {
  for (auto const & [key, val] : m) {
    out << key << " : " << val << '\n';
  }

  return out;
}

template <class T>
void print(const std::vector<T> &v) {
  for (size_t i = 0, size = v.size(); i < size; i++) {
    std::cout << v[i] << ", ";
  }

  std::cout << '\n';
}

 
// манипуляторы вывода
 
std::ostream& clrll(std::ostream& out);
std::ostream& clrl(std::ostream& out);


