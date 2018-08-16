#ifndef HIGHERPSI_H
#define HIGHERPSI_H

#include <primesieve.hpp>
#include <primecount.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <gmp.h>
#include <cmath>
#include <mpreal.h>

//The purpose of this class is have all the functionality of higherPsi in a way that makes it easier to work with
//without breaking any of the compatibility with the program. Therefore the function operator is defined.
//Essentially, by creating the capability of splitting apart HigherPsi into separate objects,
//it should become possible to take advantage of precomputed values without perfect knowledge of the order.

/*
  Goals for later:
  Save/Load
  Goals for now:
  Copy
  Primes shared across all objects (static) to save space
 */

class HigherPsi {
  private:
   long long highest;
   std::vector<mpfr::mpreal> theta;
   std::vector<long long> floorK;
   std::vector<size_t> cur;
   std::vector<long long> lastPrime;
  public:
   HigherPsi();
   HigherPsi(const HigherPsi&);
   HigherPsi& operator=(const HigherPsi&);
   bool walkK(const long long x);
   mpfr::mpreal sumThetas();
   mpfr::mpreal operator() (const long long);
   void clear();
};

//prime numbers
extern std::vector<long long> prime;
extern primesieve::iterator it;

void fillMorePrimes(long long);

//mathematical functions
unsigned long long integer_raise2(const unsigned long long);

#endif //HIGHEPSI_H
