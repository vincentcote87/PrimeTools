#include "s1.h"

mpfr::mpreal S1(const uint64_t x, const mpfr::mpreal u) {
   return primetools::calculatePsiLongDouble(static_cast<uint64_t>(u)); //floor is okay
}

