#include "HigherPsi.h"

std::vector<long long> prime;
primesieve::iterator it;

HigherPsi::HigherPsi()
   : highest{0}, theta{}, floorK{}, cur{}, lastPrime{}
{}

HigherPsi::HigherPsi(const HigherPsi& a)
   : highest{a.highest}, theta{a.theta}, floorK{a.floorK}, cur{a.cur}, lastPrime{a.lastPrime}
{}

HigherPsi& HigherPsi::operator=(const HigherPsi& a) {
   theta = a.theta;
   floorK = a.floorK;
   cur = a.cur;
   lastPrime = a.lastPrime;
   return *this;
}

//true if we walked
bool HigherPsi::walkK(const long long x) {
   bool result = false;
   long long floorXNegK;
   long long pos = 0;
   for (long long i = 1; x >= integer_raise2(i); ++i) {
      if (pos >= floorK.size()) {
	 floorK.push_back(0.0);
	 theta.push_back(0.0);
	 cur.push_back(0);
	 lastPrime.push_back(1);
      }
      floorXNegK = static_cast<long long>(std::pow(x, 1.0/static_cast<long double>(i)));
      if (floorK[pos] < floorXNegK) {
	 floorK[pos] = floorXNegK;
	 while (lastPrime[pos] <= floorXNegK) {
	    result = true;
	    theta[pos] += log(mpfr::mpreal{lastPrime[pos]}, MPFR_RNDN);
	    if (cur[pos] >= prime.size())
	       fillMorePrimes(cur[pos] + 1);
	    lastPrime[pos] = prime[cur[pos]++];
	 }
      }
      ++pos;
   }
   return result;
}

mpfr::mpreal HigherPsi::sumThetas() {
	mpfr::mpreal sum = 0.0;
	for (size_t i = 0; i < theta.size(); ++i) {
		sum += theta[i];
	}
	return sum;
}

mpfr::mpreal HigherPsi::operator() (const long long x) {
	if (x < 2)
		return 0.0;
	walkK(x);
	return sumThetas();
}

void HigherPsi::clear() {
   theta.clear();
   floorK.clear();
   cur.clear();
   lastPrime.clear();
}

void fillMorePrimes(long long target) {
	if (target <= 0) {
		target = 1;
	}
	if (target <= prime.size())
		return;
	size_t i = prime.size();
	prime.resize(target);
	for (; i < prime.size(); ++i) {
		prime[i] = it.next_prime();
	}
}

unsigned long long integer_raise2(const unsigned long long b) {
	unsigned long long a = 1;
		a <<= b;
	return a;
}
