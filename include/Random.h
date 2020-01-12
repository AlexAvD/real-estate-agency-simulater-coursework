#pragma once

#include <random>
#include <chrono>

class Random {
  private:
    static unsigned seed_;
    static std::default_random_engine engine_; 
    static std::uniform_int_distribution<int> intGen_;
    static std::uniform_real_distribution<double> doubleGen_;

    static int randInt();
    static double randDouble();

  public:
    static int getInt(int min, int max);
    static bool getBool();
    static double getDouble();
};