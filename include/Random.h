#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>

class Random {
  private:
    unsigned int m_seed;

  public:
    Random();
    Random(unsigned int seed);

    int getInt(int min, int max);
    double getDouble(double min, double max);
};