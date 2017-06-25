#include "Random.h"
#include <cstdlib>

bool Random::chance(int chance) {
    return (rand() % chance) == 0;
}
