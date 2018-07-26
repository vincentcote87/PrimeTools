#include "s1.h"

mpfr::mpreal S1(const uint64_t x, const mpfr::mpreal u) {
	mpfr::mpreal temp = psi(u.toLLong(MPFR_RNDD));
   return temp;
}
