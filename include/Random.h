#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <limits>
#include <random>
#include <chrono>
#include <functional>

class Random {
  private:
    static unsigned seed_;
    static std::default_random_engine generator_; 
    static std::uniform_int_distribution<int> dist_;

  public:
    static int getInt(int min, int max);
    static bool getBool();
};