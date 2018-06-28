#ifndef PRIMETOOLS_H
#define PRIMETOOLS_H
#include <primesieve.hpp>
#include <primecount.hpp>
#include <cmath>
#include "int_double.h"


namespace primetools {

  // callable functions
  int64_t getPi(int64_t);
  int_double calculateTheta(uint64_t);
  int_double calculateTheta(uint64_t, uint64_t);
  long double calculateThetaLongDouble(uint64_t, uint64_t);
  int_double calculatePsi(uint64_t);
  long double calculatePsiLongDouble(uint64_t);
  long double calculatePsiNoTheta(uint64_t);
  int_double logpOverp(uint64_t);

  // helper functions
  uint64_t getKValue(uint64_t);
  uint64_t nextTheta(uint64_t, long double);

}
#endif //PRIMETOOLS_H
