/*******************************************************************************
File: random.h
*******************************************************************************/
#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <ctime>

class Random {
     public:
          static void Seed(); /* Seeds the pseudo random number generator using
                                 current time */
          static void Seed(unsigned int seed); /*Specifies seed for p-RNG */
          static int Get(int max);
               /* Returns random number between 0 and max */
          static int Get(int min, int max);
               /* Returns a random number between min and max */
};

#endif
