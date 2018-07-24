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

#include "s3.h"

namespace primetools {

  // callable functions
  int64_t getPi(int64_t);
  int_double calculateTheta(uint64_t);

  int_double calculateTheta(uint64_t, uint64_t);

  mpfr::mpreal calculateThetaLongDouble(uint64_t, uint64_t);

  int_double calculatePsi(uint64_t);

  mpfr::mpreal calculatePsiLongDouble(uint64_t);

  mpfr::mpreal calculatePsiNoTheta(uint64_t);

  long long fastK(long long, long long, long long);

  int_double logpOverp(uint64_t);

  // helper functions
  uint64_t getKValue(uint64_t);

  uint64_t nextTheta(uint64_t, long double);

	long long fast_log2(const uint64_t x);
}
#endif //PRIMETOOLS_H
