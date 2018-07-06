#ifndef S4_H
#define S4_H
#include "Environment.h"
#include "Primetools.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <primesieve.hpp>
#include <primecount.hpp>
#include <climits>
#include "mpreal.h"

#include "mobius.h"
#include "N.h"

mpfr::mpreal S4(uint64_t, mpfr::mpreal);
mpfr::mpreal S4a(uint64_t, mpfr::mpreal, mpfr::mpreal);
mpfr::mpreal S4a_innerLoop(uint64_t, mpfr::mpreal, uint64_t, mpfr::mpreal);
mpfr::mpreal S4b(uint64_t, mpfr::mpreal, mpfr::mpreal);
mpfr::mpreal S4b_innerSum(uint64_t, mpfr::mpreal, uint64_t, mpfr::mpreal);

mpfr::mpreal slowS4(uint64_t x, mpfr::mpreal u);
mpfr::mpreal slowS4_inner(uint64_t x, mpfr::mpreal u, uint64_t l, mpfr::mpreal psiOfU);

#endif
