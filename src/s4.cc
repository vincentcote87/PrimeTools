#include "s4.h"

mpfr::mpreal S4(const uint64_t x, const mpfr::mpreal u) {
   mpfr::mpreal psi_of_u = primetools::calculatePsiLongDouble((uint64_t)u);
   #ifdef DEBUG
   std::cout<<"psi(u) = "<<psi_of_u<<std::endl;
   #endif //DEBUG
   //std::cout << "S4: HERE" << std::endl;
  mpfr::mpreal result = S4a(x, u, psi_of_u) + S4b(x, u, psi_of_u);
  // std::cout<<"S4 Done..."<<result<<std::endl;
  return result;
}

mpfr::mpreal S4a(const uint64_t x, const mpfr::mpreal u, const mpfr::mpreal psiOfU) {
  #ifdef DEBUG
  std::cout<<"In S4a"<<std::endl;
  #endif //DEBUG
  mpfr::mpreal result = 0.0;
  mpfr::mpreal sum = 0.0;
  for(uint64_t l = 1; l <= (uint64_t) u; ++l) { //floor was okay
    #ifdef DEBUG
    std::cout<<"l is = "<<l<<" <= "<<(uint64_t)u<<endl;
    #endif //DEBUG
    sum = mobius(l) * S4a_innerLoop(x, u, l, psiOfU);
    result += sum;
    #ifdef DEBUG
    std::cout<<"At l = "<<l<<" Mobius is = "<<mobius(l)<<" the result from the sum is = "<<sum<<" and the overall sum is = "<<result<<endl;
    #endif //DEBUG
  }
  return result;
}

mpfr::mpreal S4a_innerLoop(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
  mpfr::mpreal result = 0.0;
  const uint64_t lowerM = (uint64_t)(u/((long double) l)); //VERY LIKELY WAS A FAILURE POINT WHEN U WAS AN INTEGER
  const uint64_t upperM = sqrt(x/l);
  #ifdef DEBUG
  std::cout<<"  Bounds for m are: "<<lowerM<<" < m <= "<<upperM<<std::endl;
  #endif //DEBUG
  //std::cout << "S4a_innerLoop about to begin with the following parameters:" << std::endl;
  //std::cout << "x: " << x << " u: " << u << " l: " << l << " psiOfU: " << psiOfU << " result: " << result << " lowerM: " << lowerM << " upperM: " << upperM << std::endl;
  //std::cout << "Entering the loop now...";
  for(uint64_t m = lowerM + 1; m <= upperM; ++m) {
    long long innerTerm = floor(static_cast<long double>(x)/(static_cast<long double>(l) * static_cast<long double>(m)));
    mpfr::mpreal firstTerm = primetools::calculatePsiLongDouble(innerTerm);
    result += (firstTerm - psiOfU);
    #ifdef DEBUG
    std::cout<<"  At m = "<<m<<" current psi is = "<<firstTerm<<" psi - psi(u) = "<<firstTerm - psiOfU<<endl;
    #endif //DEBUG
  }
  #ifdef DEBUG
  std::cout<<"  Returning sum = "<<result<<std::endl;
  #endif //DEBUG
  return result;
}

mpfr::mpreal S4b(const uint64_t x, const mpfr::mpreal u, const mpfr::mpreal psiOfU) {
  #ifdef DEBUG
  std::cout<<"In S4b"<<std::endl;
  #endif //DEBUG
   mpfr::mpreal result = 0.0;
   mpfr::mpreal sum = 0.0;
   long long mu = 0;
   for (uint64_t l = 1; l <= (uint64_t) u; ++l) { //floor was ok
     mu = mobius(l);
     #ifdef DEBUG
     std::cout<<"l is = "<<l<<" <= "<<(uint64_t)u<<endl;
     #endif //DEBUG
     if(mu != 0 && (((long long) std::sqrt(((long double) x)/((long double) l))) < static_cast<long long>(x/(u * static_cast<long double>(l))))) {
        sum = mu*S4b_innerSum(x, u, l, psiOfU);
        result += sum;
     }
      #ifdef DEBUG
      std::cout<<"At l = "<<l<<" Mobius is = "<<mobius(l)<<" the result from the sum is = "<<sum<<" and the overall sum is = "<<result<<endl;
      #endif //DEBUG
   }
   #ifdef DEBUG
   std::cout << "Leaving S4b" << std::endl;
   #endif
   return result;
}

mpfr::mpreal S4b_innerSum(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
   mpfr::mpreal sum = 0.0;
   const long double end = std::sqrt(x/l); //k <= sqrt(x/l), k is an integer...
   //std::cout << "S4b_innerSum about to begin with the following parameters:" << std::endl;
   //std::cout << "x: " << x << " u: " << u << " l: " << l << " psiOfU: " << psiOfU << " sum: " << sum << " end: " << end << std::endl;
   //std::cout << "Entering the loop now...";
   #ifdef DEBUG
   std::cout<<"  Bounds for k: 0 < k <= "<<end<<endl;
   #endif //DEBUG
   for (uint64_t k = 1; k <= end; ++k) {
      const long long n = N(x, u, l, k);
      #ifdef DEBUG
      std::cout<<"    @k = "<<k<<" N = "<<n;
      #endif //DEBUG
      if (n != 0) {
        #ifdef DEBUG
        std::cout<<" psi(k) = "<<primetools::calculatePsiLongDouble(k)<<" and the result is = "<<(primetools::calculatePsiLongDouble(k) - psiOfU)*n;
        #endif //DEBUG
	       sum += (primetools::calculatePsiLongDouble(k) - psiOfU)*n;
      }
      #ifdef DEBUG
      std::cout<<endl;
      #endif //DEBUG
   }
   //std::cout << "S4b_innerSum returning the sum" << sum << std::endl;
   return sum;
}



mpfr::mpreal slowS4(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal psi_of_u = primetools::calculatePsiLongDouble((uint64_t)u);
  #ifdef DEBUG
  std::cout<<"psi(u) = "<<psi_of_u<<std::endl;
  #endif //DEBUG
  mpfr::mpreal result = 0.0;
  for(uint64_t l = 1; l <= (uint64_t) u; ++l) { //floor was ok
    #ifdef DEBUG
    std::cout<<l<<" <= "<<(uint64_t)u<<endl;
    #endif //DEBUG
    mpfr::mpreal sum = (mobius(l) * slowS4_inner(x, u, l, psi_of_u));
    result += sum;
    #ifdef DEBUG
    std::cout<<"At l = "<<l<<" Mobius is = "<<mobius(l)<<" the result from the sum is = "<<sum<<" and the overall sum is = "<<result<<endl;
    #endif //DEBUG
    // std::cout<<"s4("<<l<<") = "<<result<<std::endl;
  }
  // std::cout<<"S4 Done..."<<result<<std::endl;
  return result;
}


//Wed June 27 3:49pm: No time to double check that u is genuinely treated as a long double for this function.
mpfr::mpreal slowS4_inner(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
  mpfr::mpreal result = 0.0;
  long long lowerBound = (long long)(u/static_cast<long double>(l)) + 1;
  long long upperBound = (long long)(static_cast<long double>(x)/(u * static_cast<long double>(l)));
  #ifdef DEBUG
  std::cout<<lowerBound<<" < m <= "<<upperBound<<endl;
  #endif //DEBUG
  for(long long m = lowerBound; m <= upperBound; ++m) {
    long long innerTerm = floor(static_cast<long double>(x)/(static_cast<long double>(l) * static_cast<long double>(m)));
    mpfr::mpreal firstTerm = primetools::calculatePsiLongDouble(innerTerm);
    // std::cout<<"psi("<<innerTerm<<") = "<<firstTerm<<std::endl;
    result += (firstTerm - psiOfU);
    #ifdef DEBUG
    std::cout<<"  At m = "<<m<<" current psi is = "<<firstTerm<<" psi - psi(u) = "<<firstTerm - psiOfU<<endl;
    #endif //DEBUG
  }
  #ifdef DEBUG
  std::cout<<"  Returning sum = "<<result<<std::endl;
  #endif //DEBUG
  return result;
}
