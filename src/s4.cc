#include "s4.h"

mpfr::mpreal S4(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal psi_of_u = getSmallPsi(u.toLLong(MPFR_RNDD));

  #ifdef DEBUG_S4
  std::cout<<"psi(u) = "<<psi_of_u<<std::endl;
  #endif //DEBUG_S4

  mpfr::mpreal result = S4a(x, u, psi_of_u);
  result += S4b(x, u, psi_of_u);
  return result;
}

mpfr::mpreal S4a(const uint64_t x, const mpfr::mpreal u, const mpfr::mpreal psiOfU) {
	mpfr::mpreal result = 0.0;
	const long long u_integer = u.toLLong(MPFR_RNDD);
	for (long long l = 1; l <= u_integer; ++l) {

    #ifdef DEBUG_S4
		std::cout << "S4a_innerloop**********************************" << std::endl;
    std::cout << "l = " << l << ", Now modbius(l) = " << mobius(l) << std::endl;
    #endif //DEBUG_S4

    mpfr::mpreal sum = (mobius(l) *S4a_innerLoop(x, u, l, psiOfU));
    result += sum;

    #ifdef DEBUG_S4
		std::cout << "S4a main sum = " << result << std::endl;
    #endif //DEBUG_S4

	}
	return result;
}

mpfr::mpreal S4a_innerLoop(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
  mpfr::mpreal result = 0.0;
  const long long lowerBound = (u/static_cast<mpfr::mpreal>(l)).toLLong(MPFR_RNDD) + 1;
  const long long a = (long long)(static_cast<long double>(x)/(u * static_cast<long double>(l)));
  const long long b = (long long)(sqrt(static_cast<long double>(x)/static_cast<long double>(l)));
  const long long upperBound = std::min(a,b);

  #ifdef DEBUG_S4
  std::cout<<"  Bounds for m are: "<<(u/static_cast<mpfr::mpreal>(l))<<" < m <= "<<upperBound<<std::endl;
  #endif //DEBUG_S4

  for(long long m = lowerBound; m <= upperBound; ++m) {
    long long innerTerm = floor(static_cast<long double>(x)/(static_cast<long double>(l) * static_cast<long double>(m)));
    mpfr::mpreal firstTerm = getSmallPsi(innerTerm);
    result += (firstTerm - psiOfU);

    #ifdef DEBUG_S4
    std::cout<<"    At m = "<<m<<" current psi is = "<<firstTerm<<" psi - psi(u) = "<<firstTerm - psiOfU<<endl;
    #endif //DEBUG_S4
  }

  #ifdef DEBUG_S4
  std::cout<<"  Returning sum = "<<result<<std::endl;
  #endif //DEBUG_S4

  return result;
}

mpfr::mpreal S4b(const uint64_t x, const mpfr::mpreal u, const mpfr::mpreal psiOfU) {
	mpfr::mpreal result = 0.0;
	const long long u_integer = u.toLLong(MPFR_RNDD);
	for (long long l = 1; l <= u_integer; ++l) {

    #ifdef DEBUG_S4
    std::cout << "S4b innerSum*************************************\n";
    std::cout << "Now modbius(l) = " << mobius(l) << std::endl;
    #endif //DEBUG_S4

		result += static_cast<mpfr::mpreal>(mobius(l)) * S4b_innerSum(x, u, l, psiOfU);

    #ifdef DEBUG_S4
    std::cout << "end of S4b_innerSum***********************************" << std::endl;
    #endif //DEBUG_S4

	}
	return result;
}

mpfr::mpreal S4b_innerSum(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
   mpfr::mpreal sum = 0.0;
   const uint64_t end = std::sqrt(((long double) x)/((long double) l)); //k <= sqrt(x/l), k is an integer...

   #ifdef DEBUG_S4
   std::cout<<"  Bounds for k: 0 < k <= "<<end<<endl;
   #endif //DEBUG_S4

   for (uint64_t k = 1; k <= end; ++k) {
      const long long n = N(x, u, l, k);

      #ifdef DEBUG_S4
      std::cout<<"    @k = "<<k<<" N("<<x<<", u, "<<l<<", "<<k<<") = "<<n;
      #endif //DEBUG_S4

      if (n != 0) {

        #ifdef DEBUG_S4
        std::cout<<" psi(k) = "<<getSmallPsi(k)<<" and the result is = "<<(getSmallPsi(k) - psiOfU)*n;
        #endif //DEBUG_S4

	       sum += (getSmallPsi(k) - psiOfU) * (n);
      }

      #ifdef DEBUG_S4
      std::cout<<endl;
      #endif //DEBUG_S4

   }
   return sum;
}

mpfr::mpreal slowS4(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal psi_of_u = primetools::calculatePsiLongDouble(u.toLLong(MPFR_RNDD));
  mpfr::mpreal result = 0.0;
  #ifdef DEBUG_SlowS4
  std::cout<<"Psi(u) = "<<psi_of_u<<endl;
  #endif //DEBUG_SlowS4
  for(uint64_t l = 1; l <= (uint64_t) u; ++l) { //floor was ok
    mpfr::mpreal sum = (mobius(l) * slowS4_inner(x, u, l, psi_of_u));
    result += sum;
    #ifdef DEBUG_SlowS4
    std::cout<<"  At L = "<<l<<" The running sum is "<<result<<std::endl;
    #endif //DEBUG_SlowS4
  }
  return result;
}


mpfr::mpreal slowS4_inner(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
  mpfr::mpreal result = 0.0;
  long long lowerBound = (long long)(u/static_cast<long double>(l)) + 1;
  long long upperBound = (long long)(static_cast<long double>(x)/(u * static_cast<long double>(l)));
  #ifdef DEBUG_SlowS4
  std::cout<<"    Inner loop "<<lowerBound<<" < m <= "<<upperBound<<std::endl;
  #endif //DEBUG_SlowS4
  for(long long m = lowerBound; m <= upperBound; ++m) {
    long long innerTerm = floor(static_cast<long double>(x)/(static_cast<long double>(l) * static_cast<long double>(m)));
    mpfr::mpreal firstTerm = primetools::calculatePsiLongDouble(innerTerm);
    result += (firstTerm - psiOfU);
    #ifdef DEBUG_SlowS4
    std::cout<<"      m"<<m<<" = "<<firstTerm<<" - "<<psiOfU<<" = "<<firstTerm-psiOfU<<std::endl;
    std::cout<<"        Running result = "<<result<<std::endl;
    #endif //DEBUG_SlowS4
  }
  return result;
}
