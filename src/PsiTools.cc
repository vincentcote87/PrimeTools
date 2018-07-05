#include "PsiTools.h"

void setupEnvironment() {
  std::cout << std::setprecision(36) << std::scientific;
  psi_setup();
  mobius_setup();
  mpfr::mpreal::set_default_prec(256);
}

void mobius_setup() {
  std::cout<<"seting up mobius table...";
  mobiusTable = new long long[mobiusCutoff];
  for (uint i = 0; i < mobiusCutoff; ++i) {
    // mobiusTable[i] = -2000;
    mobiusTable[i] = mobius_work(i);
  }
  std::cout<<"Done"<<std::endl;
}

void psi_setup() {
  std::cout<<"seting up psi table...";
  psiTable = new mpfr::mpreal[cutoff];
  for (uint i = 0; i < cutoff; ++i) {
    psiTable[i] = 0;
  }
  std::cout<<"Done"<<std::endl;
}

mpfr::mpreal psi(uint64_t x) {
  if (x < 2)
    return 0.0;
  if (x < cutoff) {
    if (psiTable[x] == 0.0) {
      psiTable[x] = psi_work(x);
    }
    return psiTable[x];
  }
  return psi_work(x);
}

mpfr::mpreal psi_work(uint64_t x) {
  if (x < 2)
    return 0.0;
  mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
  // if (u < 1)
  //   u = 1;
  // return S1(x, u) + S2(x, u) - S3(x, u) - slowS4(x, u);
  return S1(x, u) + S2(x, u) - S3(x, u) - S4(x, u);
}
//TODO Make T use mpreal as well?
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

mpfr::mpreal S1(const uint64_t x, const mpfr::mpreal u) {
   return primetools::calculatePsiLongDouble(static_cast<uint64_t>(u)); //floor is okay
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

uint64_t pow(const uint64_t a, const uint64_t b) {
   if (b == 0)
      return 1;
   if (b == 1)
      return a;
   const uint64_t half = pow(a, b/2);
   if (b%2 == 0)
      return half*half;
   return half*half*a;
}

long long S3_B(const uint64_t x, const mpfr::mpreal u, const uint64_t p, const uint64_t l) {
  long long result = 0;
  const uint64_t L = (uint64_t) (log(u, GMP_RNDN)/log((mpfr::mpreal) p, GMP_RNDN)); //intentional floor //FLOOR OF U MIGHT BE NOT OK
  for (uint64_t k = 1; k <= L; ++k) {
    result += x / (l * pow( p, k)); //intentional floor
  }
  // std::cout<< " result from S3_B = "<<result<<std::endl;
  return result;
}

mpfr::mpreal S3_A(const uint64_t x, const mpfr::mpreal u, const uint64_t p) {
  mpfr::mpreal S = 0.0;
  // uint64_t tmpMu = 0;
  for (uint64_t l = 1; l <= u.toLLong(GMP_RNDD); ++l) { //floor was okay for less than or equal to u
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

long long mobius (long long x) {
  if (x < mobiusCutoff) {
    if (mobiusTable[x] == -2000)
      mobiusTable[x] = mobius_work(x);
    return mobiusTable[x];
  }
  return mobius_work(x);
}

long long mobius_work(long long x) {

  long long k = 0;
  if(x == 1)
    return 1;
  if(x == 2)
    return -1;
  if(x % 2 == 0) {
    x = x / 2;
    k++;
    if(x % 2 == 0)
      return 0;
  }

  for(long long i = 3; i*i <= x; i += 2) {
    if(x % i == 0) {
      x = x / i;
      k++;
      if(x % i == 0)
        return 0;
    }
  }
  return (k % 2 == 0) ? -1 : 1;
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
