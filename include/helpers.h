#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <functional>

void setRus();

std::vector<std::string> tokenize(const std::string & str, char separator);
std::string normalizeLine(const std::string & str);
std::string concat(const std::vector<std::string> & strings, char ch);
