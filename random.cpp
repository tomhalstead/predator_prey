/*******************************************************************************
File: random.cpp
*******************************************************************************/
#include "random.h"

void Random::Seed() {
    srand(time(NULL));
}
void Random::Seed(unsigned int seed) {
    srand(seed);
}
int Random::Get(int max) {
     return rand() % (max+1);
}
int Random::Get(int min, int max) {
    int result = max - min + 1;
    result = rand() % result;
    result += min;
    return result;
}
