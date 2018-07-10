#include "Primetools.h"


int64_t primetools::getPi(int64_t x) {
  return primecount::pi(x);
}

int_double primetools::calculateTheta(uint64_t x) {
   if (x < 2)
      return int_double{0.0};
  return primetools::calculateTheta(0, x);
}

int_double primetools::calculateTheta(uint64_t start, uint64_t stop) {
  int_double theta = 0.0;
	int_double temp = 0.0;
	int_double y = 0.0;
	int_double errorTerm = 0.0;

  primesieve::iterator it;
  it.skipto(start);
  uint64_t prime = it.next_prime();

  for (; prime <= stop; prime = it.next_prime()) {
    y = log(prime) - errorTerm;
    temp = theta + y;
    errorTerm = (temp - theta) - y;
    theta = temp;
  }

  return theta;
}

mpfr::mpreal primetools::calculateThetaLongDouble(uint64_t start, uint64_t stop) {
  mpfr::mpreal theta = 0.0;
	mpfr::mpreal temp = 0.0;
	mpfr::mpreal y = 0.0;
	mpfr::mpreal errorTerm = 0.0;
  mpfr::mpreal x = 0;

  primesieve::iterator it;
  it.skipto(start);
  uint64_t prime = it.next_prime();

  for (; prime <= stop; prime = it.next_prime()) {
    x = prime;
    y = log(x, MPFR_RNDN) - errorTerm;
    temp = theta + y;
    errorTerm = (temp - theta) - y;
    theta = temp;
  }

  return theta;
}

int_double primetools::calculatePsi(uint64_t x) {
   if (x < 2)
      return int_double{0.0};
  int_double psi = 0.0;
  uint64_t k = primetools::getKValue(x);
  uint64_t tmpX = primetools::nextTheta(x, k);

	while(k > 0) {
		psi += primetools::calculateTheta(0, tmpX);
		tmpX = primetools::nextTheta(x, --k);
	}
  return psi;
}

mpfr::mpreal primetools::calculatePsiLongDouble(uint64_t x) {
   if (x < 2)
      return 0.0;
  mpfr::mpreal psi = 0.0;
  if(x < 2)
    return psi;
  uint64_t k = primetools::getKValue(x);
  uint64_t tmpX = primetools::nextTheta(x, k);

	while(k > 0) {
		psi += primetools::calculateThetaLongDouble(0, tmpX);
		tmpX = primetools::nextTheta(x, --k);
	}
  return psi;
}

long long primetools::fast_log2(const uint64_t x) {
	uint64_t y;
	asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  //std::cout << "fast_log2(" << x << ") = " << y << std::endl;
  return y;
}

long long primetools::fastK(const long long x, const long long p, const long long start) {
	if (start == 0) {
		if (p == 2)
			return fast_log2(x);
		long long i = 0;
		for (long long spar = p; spar <= x; spar*=p) ++i;
		return i;
	}
	long long i = start;
	for (long long spar = floor_pow(p, start); spar > x; spar/=p) --i;
	return i;
}

mpfr::mpreal primetools::calculatePsiNoTheta(const uint64_t arg) {
   if (arg < 2)
      return 0.0L;
      mpfr::mpreal x = arg;
  mpfr::mpreal psi = 0.0;
	mpfr::mpreal temp = 0.0;
	mpfr::mpreal y = 0.0;
	mpfr::mpreal errorTerm = 0.0;
	long long k_temp = 0;
	mpfr::mpreal k;

  primesieve::iterator it;
  it.skipto(0);
  uint64_t prime = it.next_prime();
  for (; prime <= x; prime = it.next_prime()) {
    k = k_temp = fastK(arg, prime, k_temp); //floor(log(x, MPFR_RNDN)/logOfPrime);
    y = (log(mpfr::mpreal{prime}, MPFR_RNDN) * k) - errorTerm;
    temp = psi + y;
    errorTerm = (temp - psi) - y;
    psi = temp;

  }
  return psi;
}

int_double primetools::logpOverp(uint64_t x) {
  return -1.0;
}

uint64_t primetools::getKValue(uint64_t x) {
	return floor((log(x)/log(2)));
}

uint64_t primetools::nextTheta(uint64_t x, long double k) {
	return floor(pow(x, (1.0/k)));
}
