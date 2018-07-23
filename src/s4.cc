#include "s4.h"

mpfr::mpreal S4(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal::set_default_prec(256);
   mpfr::mpreal psi_of_u = primetools::calculatePsiLongDouble(u.toLLong(MPFR_RNDD));
   #ifdef DEBUG_S4
   std::cout<<"psi(u) = "<<psi_of_u<<std::endl;
   #endif //DEBUG_S4
   //std::cout << "S4: HERE" << std::endl;
  mpfr::mpreal result = S4a(x, u, psi_of_u);
  result += S4b(x, u, psi_of_u);
  #ifdef DEBUG_S4
  #endif //DEBUG_S4
  // std::cout<<"S4 Done..."<<result<<std::endl;
  return result;
}

mpfr::mpreal S4a(const uint64_t x, const mpfr::mpreal u, const mpfr::mpreal psiOfU) {
	mpfr::mpreal result = 0.0;
	const long long u_integer = (long long) floor(u);
	for (long long l = 1; l <= u_integer; ++l) {
    #ifdef DEBUG_S4
		std::cout << "S4a_innerloop**********************************" << std::endl;
    std::cout << "l = " << l << ", Now modbius(l) = " << mobius(l) << std::endl;
    #endif //DEBUG_S4
    mpfr::mpreal sum = (mobius(l) *S4a_innerLoop(x, u, l, psiOfU));
    result += sum;
		// result += static_cast<mpfr::mpreal>(mobius(l)) * S4a_innerLoop(x, u, l, psiOfU);
    // #ifdef DEBUG_S4
		// std::cout << "end of S4a_innerloop***********************************" << std::endl;
    // #endif //DEBUG_S4
	}
	return result;
}

mpfr::mpreal S4a_innerLoop(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
  mpfr::mpreal result = 0.0;
  const long long lowerBound = (u/static_cast<mpfr::mpreal>(l)).toLLong(MPFR_RNDD) + 1;
  const long long upperBound = (long long)(sqrt(static_cast<long double>(x)/static_cast<long double>(l)));
  // const uint64_t lowerM = (uint64_t)(u.toLDouble(MPFR_RNDN)/static_cast<long double>(l)); //VERY LIKELY WAS A FAILURE POINT WHEN U WAS AN INTEGER
  // const uint64_t upperM = sqrt(static_cast<long double>(x)/static_cast<long double>(l));

  #ifdef DEBUG_S4
  std::cout<<"  Bounds for m are: "<<(u/static_cast<mpfr::mpreal>(l))<<" < m <= "<<upperBound<<std::endl;
  #endif //DEBUG_S4

  //std::cout << "S4a_innerLoop about to begin with the following parameters:" << std::endl;
  //std::cout << "x: " << x << " u: " << u << " l: " << l << " psiOfU: " << psiOfU << " result: " << result << " lowerM: " << lowerM << " upperM: " << upperM << std::endl;
  //std::cout << "Entering the loop now...";
  for(long long m = lowerBound; m <= upperBound; ++m) {
    long long innerTerm = floor(static_cast<long double>(x)/(static_cast<long double>(l) * static_cast<long double>(m)));
    // std::cout<<"    innerfloor with L = "<<l<<" and m = "<<m<<" is "<<innerTerm<<std::endl;
    mpfr::mpreal firstTerm = primetools::calculatePsiLongDouble(innerTerm);
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
	const long long u_integer = (long long) floor(u);
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
   const long long end = std::sqrt(((long double) x)/((long double) l)); //k <= sqrt(x/l), k is an integer...
   //std::cout << "S4b_innerSum about to begin with the following parameters:" << std::endl;
   //std::cout << "x: " << x << " u: " << u << " l: " << l << " psiOfU: " << psiOfU << " sum: " << sum << " end: " << end << std::endl;
   //std::cout << "Entering the loop now...";
   #ifdef DEBUG_S4
   std::cout<<"  Bounds for k: 0 < k <= "<<end<<endl;
   #endif //DEBUG_S4
   for (uint64_t k = 1; k <= end; ++k) {
      const long long n = N(x, u, l, k);
      // const long long n = slowN(x, u, l, k);
      #ifdef DEBUG_S4
      std::cout<<"    @k = "<<k<<" N("<<x<<", u, "<<l<<", "<<k<<") = "<<n;
      #endif //DEBUG_S4
      if (n != 0) {
        #ifdef DEBUG_S4
        std::cout<<" psi(k) = "<<primetools::calculatePsiLongDouble(k)<<" and the result is = "<<(primetools::calculatePsiLongDouble(k) - psiOfU)*n;
        #endif //DEBUG_S4
	       sum += (primetools::calculatePsiLongDouble(k) - psiOfU) * (n);
      }
      #ifdef DEBUG_S4
      std::cout<<endl;
      #endif //DEBUG_S4
   }
   //std::cout << "S4b_innerSum returning the sum" << sum << std::endl;
   return sum;
}



mpfr::mpreal slowS4(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal::set_default_prec(256);
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
