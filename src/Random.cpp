#include "Random.h"

Random::Random() {
  m_seed = time(0); 
  srand(m_seed);
}

Random::Random(unsigned int seed = time(0)) : m_seed(seed) {
  srand(m_seed);
}

int Random::getInt(int min = 0, int max = 1) {
  return min + rand() % (max - min + 1);
}
 
double Random::getDouble(double min = 0, double max = 1) {
  return min + (rand() / (double)RAND_MAX) * (max - min);
} 