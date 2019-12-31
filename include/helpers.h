#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>


void setRus();

bool isBlank(const std::string & str);
std::vector<std::string> tokenize(const std::string & str, char separator);
std::string normalizeLine(const std::string & str);
std::string concat(const std::vector<std::string> & strings, char ch);
std::string trim(const std::string & str);

std::vector<std::map<std::string, std::string>> readFile(const std::string & fileName);

template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> & v) {
  for (size_t i = 0, len = v.size(); i < len; i++) {
    out << v[i] << '\n';
  }

  return out;
}

template <class T, class L> 
std::ostream& operator<<(std::ostream &out, const std::map<T, L> & m) {
  for (auto const & [key, val] : m) {
    out << key << " : " << val << '\n';
  }

  return out;
}
