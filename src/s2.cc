#include "s2.h"

mpfr::mpreal T(uint64_t arg) {
  mpfr::mpreal N = (mpfr::mpreal) arg;
  mpfr::mpreal T1 = 0.0;
  mpfr::mpreal T2 = 0.0;
  mpfr::mpreal T3 = 0.0;

  T1 = ((N + (mpfr::mpreal{1.0}/mpfr::mpreal{2.0})) * log(N, GMP_RNDN)) - N;
  T2 = (mpfr::mpreal{1.0}/mpfr::mpreal{2.0}) * log(mpfr::mpreal{2.0} * PI, GMP_RNDN);

  for(int j = 1; j <= J; j++) {
    T3 += ((B2[j])/(mpfr::mpreal{2.0} * j * ((mpfr::mpreal{2.0} * j) - mpfr::mpreal{1.0}) * pow(N,((mpfr::mpreal{2.0} * j) - mpfr::mpreal{1.0}), GMP_RNDN)));
  }

  return T1 + T2 + T3;
}

mpfr::mpreal S2(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal S = 0.0;
  mpfr::mpreal mob;
  mpfr::mpreal directSum;
  #ifdef DEBUG_S2
  std::cout << "m from 1 through u = " << u << std::endl;
  #endif //DEBUG_S2
  for(uint64_t m = 1; m <= (uint64_t) u; m++) { //floor is okay
    mob = mobius(m);
    #ifdef DEBUG_S2
    std::cout << " " << "m = " << m << " mobius(m) = " << mob << std::endl;
    #endif //DEBUG_S2
    if (mob == 0) {
      continue;
    }
    uint64_t S2b = x/m;
    #ifdef DEBUG_S2
    std::cout << " " << "S2b aka floor(x/m)= " << S2b;
    #endif //DEBUG_S2
    if(S2b > 100000) {
      #ifdef DEBUG_S2
    std::cout << "T(x/m) * mobius(m) = " << mob * T(x/m);
    #endif //DEBUG_S2
      S += mob * T(x/m);
    }
    else {
      directSum = 0.0;
      for(uint64_t i = 1; i <= S2b; ++i)
        directSum += log((mpfr::mpreal) i, GMP_RNDN);
      S += mob * directSum;
    }
    #ifdef DEBUG_S2
    std::cout << "directSum(1 through x/m) * mobius(m) = " << (directSum * mob);
    std::cout << " now S is " << S << std::endl;
    #endif //DEBUG_S2
  }
  return S;
}
