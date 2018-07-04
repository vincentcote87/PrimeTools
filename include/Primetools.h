#ifndef PRIMETOOLS_H
#define PRIMETOOLS_H
#include "Environment.h"
#include <gmp.h>
#include <stdio.h>
#include <mpfr.h>
#include <primesieve.hpp>
#include <primecount.hpp>
#include <cmath>
#include "int_double.h"
#include "mpreal.h"


namespace primetools {

  // callable functions
  int64_t getPi(int64_t);
  int_double calculateTheta(uint64_t);
  int_double calculateTheta(uint64_t, uint64_t);
  mpfr::mpreal calculateThetaLongDouble(uint64_t, uint64_t);
  int_double calculatePsi(uint64_t);
  mpfr::mpreal calculatePsiLongDouble(uint64_t);
  long double calculatePsiNoTheta(uint64_t);
  int_double logpOverp(uint64_t);
  // const int DIGITS = 256;
  // long double log(long double a, int digits = DIGITS);

  // helper functions
  uint64_t getKValue(uint64_t);

  uint64_t nextTheta(uint64_t, long double);


}
#endif //PRIMETOOLS_H
