#include "Random.h"

unsigned Random::seed_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();

std::default_random_engine Random::engine_(Random::seed_);

std::uniform_int_distribution<int> Random::gen_(0, INT_MAX);

int Random::getInt(int min = 0, int max = RAND_MAX) {
  return min + randInt() % (max - min + 1);
}

bool Random::getBool() {
  return (bool)getInt(0, 1);
}

int Random::randInt() {
  return gen_(engine_);
}
  