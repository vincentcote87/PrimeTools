#include "s3.h"

uint64_t floor_pow(const uint64_t a, const uint64_t b) {
   if (b == 0)
      return 1;
   if (b == 1)
      return a;
   const uint64_t half = floor_pow(a, b/2);
   if (b%2 == 0)
      return half*half;
   return half*half*a;
}

long long S3_B(const uint64_t x, const mpfr::mpreal u, const uint64_t p, const uint64_t l) {
  long long result = 0;
  const uint64_t L = (uint64_t) (log(u, GMP_RNDN)/log((mpfr::mpreal) p, GMP_RNDN)); //intentional floor //FLOOR OF U MIGHT BE NOT OK
  for (uint64_t k = 1; k <= L; ++k) {
    result += x / (l * floor_pow( p, k)); //intentional floor
  }
  // std::cout<< " result from S3_B = "<<result<<std::endl;
  return result;
}

mpfr::mpreal S3_A(const uint64_t x, const mpfr::mpreal u, const uint64_t p) {
  mpfr::mpreal S = 0.0;
  // uint64_t tmpMu = 0;
  for (long long l = 1; l <= u.toLLong(GMP_RNDD); ++l) { //floor was okay for less than or equal to u
    S += mobius(l)*S3_B(x, u, p, l);
    // tmpMu += mobius(l);
    // std::cout<<tmpMu<<std::endl;
  }
  return S;
}

mpfr::mpreal S3(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal S = 0.0;
  mpfr::mpreal p = 0;

  primesieve::iterator it;
  it.skipto(0);
  uint64_t prime = it.next_prime();

  for (; prime <= (uint64_t) u; prime = it.next_prime()) { //floor is okay for less than or equal to u
    p = prime;
    S += log(p, GMP_RNDN)*S3_A(x, u, prime);
    // std::cout<<S<<std::endl;
  }
  // std::cout<<u<<std::endl;
  //std::cout<<"S3 Done..."<<S<<std::endl;
  return S;
}
