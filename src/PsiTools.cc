#include "PsiTools.h"

void setupEnvironment() {
  std::cout << std::setprecision(36) << std::scientific;
  psi_setup();
  mobius_setup();
  mpfr::mpreal::set_default_prec(256);
}

// const uint64_t mobiusCutoff = 3000000;
// long long *mobiusTable;
void mobius_setup() {
  std::cout<<"seting up mobius table...";
  mobiusTable = new long long[mobiusCutoff];
  for (uint i = 0; i < mobiusCutoff; ++i) {
    // mobiusTable[i] = -2000;
    mobiusTable[i] = mobius_work(i);
  }
  std::cout<<"Done"<<std::endl;
}

// const size_t cutoff = 10000000; //4294967295
// long double *psiTable;

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
  return S1(x, u) + S2(x, u) - S3(x, u) - slowS4(x, u);
  // return S1(x, u) + S2(x, u) - S3(x, u) - S4(x, u);
}
//TODO Make T use mpreal as well?
long double T(long double t) {
  uint64_t N = floor(t);
  long double T1 = 0.0;
  long double T2 = 0.0;
  long double T3 = 0.0;

  T1 = ((N + (1.0/2.0)) * log(N)) - N;
  T2 = (1.0/2.0) * log(2.0 * PI);

  for(int j = 1; j <= J; j++) {
    T3 += ((B2[j])/(2.0 * j * ((2.0 * j) - 1.0) * pow(N,((2.0 * j) - 1.0))));
  }

  return T1 + T2 + T3;
}

mpfr::mpreal S1(const uint64_t x, const mpfr::mpreal u) {
   return primetools::calculatePsiLongDouble(static_cast<uint64_t>(u)); //floor is okay
}

mpfr::mpreal S2(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal S = 0.0;
  uint64_t S2b = 0;

  for(uint64_t m = 1; m <= (uint64_t) u; m++) { //floor is okay
    S2b = x/m;
    mpfr::mpreal sum = 0.0;
    if(S2b > 100000)
    // if(true)
      S += static_cast<mpfr::mpreal>(mobius(m)) * T(x/m);
    else {
      for(uint i = 1; i <= S2b; ++i)
        sum += log(i);
      S += static_cast<mpfr::mpreal>(mobius(m)) * sum;
    }
  }
  //std::cout<<"S2 Done..."<<S<<std::endl;
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
  const uint64_t L = (uint64_t) (log(u, MPFR_RNDN)/log((mpfr::mpreal) p, MPFR_RNDN)); //intentional floor //FLOOR OF U MIGHT BE NOT OK
  for (uint64_t k = 1; k <= L; ++k) {
    result += x / (l * pow( p, k)); //intentional floor
  }
  // std::cout<< " result from S3_B = "<<result<<std::endl;
  return result;
}

mpfr::mpreal S3_A(const uint64_t x, const mpfr::mpreal u, const uint64_t p) {
  mpfr::mpreal S = 0.0;
  // uint64_t tmpMu = 0;
  for (uint64_t l = 1; l <= (uint64_t) u; ++l) { //floor was okay for less than or equal to u
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
    S += log(p, MPFR_RNDN)*S3_A(x, u, prime);
    // std::cout<<S<<std::endl;
  }
  // std::cout<<u<<std::endl;
  //std::cout<<"S3 Done..."<<S<<std::endl;
  return S;
}
mpfr::mpreal S4(const uint64_t x, const mpfr::mpreal u) {
   mpfr::mpreal psi_of_u = primetools::calculatePsiLongDouble((uint64_t)u);
   std::cout<<"psi(u) = "<<psi_of_u<<std::endl;
   //std::cout << "S4: HERE" << std::endl;
  mpfr::mpreal result = S4a(x, u, psi_of_u) + S4b(x, u, psi_of_u);
  // std::cout<<"S4 Done..."<<result<<std::endl;
  return result;
}

mpfr::mpreal S4a(const uint64_t x, const mpfr::mpreal u, const mpfr::mpreal psiOfU) {
  std::cout<<"In S4a"<<std::endl;
  mpfr::mpreal result = 0.0;
  mpfr::mpreal sum = 0.0;
  for(uint64_t l = 1; l <= (uint64_t) u; ++l) { //floor was okay
    std::cout<<"l is = "<<l<<" <= "<<(uint64_t)u<<endl;
    sum = mobius(l) * S4a_innerLoop(x, u, l, psiOfU);
    result += sum;
    std::cout<<"At l = "<<l<<" Mobius is = "<<mobius(l)<<" the result from the sum is = "<<sum<<" and the overall sum is = "<<result<<endl;
  }
  return result;
}

mpfr::mpreal S4a_innerLoop(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
  mpfr::mpreal result = 0.0;
  const uint64_t lowerM = (uint64_t)(u/((long double) l)); //VERY LIKELY WAS A FAILURE POINT WHEN U WAS AN INTEGER
  const uint64_t upperM = sqrt(x/l);
  std::cout<<"  Bounds for m are: "<<lowerM<<" < m <= "<<upperM<<std::endl;
  //std::cout << "S4a_innerLoop about to begin with the following parameters:" << std::endl;
  //std::cout << "x: " << x << " u: " << u << " l: " << l << " psiOfU: " << psiOfU << " result: " << result << " lowerM: " << lowerM << " upperM: " << upperM << std::endl;
  //std::cout << "Entering the loop now...";
  for(uint64_t m = lowerM + 1; m <= upperM; ++m) {
    long long innerTerm = floor(static_cast<long double>(x)/(static_cast<long double>(l) * static_cast<long double>(m)));
    mpfr::mpreal firstTerm = primetools::calculatePsiLongDouble(innerTerm);
    result += (firstTerm - psiOfU);
    std::cout<<"  At m = "<<m<<" current psi is = "<<firstTerm<<" psi - psi(u) = "<<firstTerm - psiOfU<<endl;
  }
  std::cout<<"  Returning sum = "<<result<<std::endl;
  return result;
}

mpfr::mpreal S4b(const uint64_t x, const mpfr::mpreal u, const mpfr::mpreal psiOfU) {
  std::cout<<"In S4b"<<std::endl;
   mpfr::mpreal result = 0.0;
   mpfr::mpreal sum = 0.0;
   for (uint64_t l = 1; l <= (uint64_t) u; ++l) { //floor was ok
     std::cout<<"l is = "<<l<<" <= "<<(uint64_t)u<<endl;
      sum = mobius(l)*S4b_innerSum(x, u, l, psiOfU);
      result += sum;
      std::cout<<"At l = "<<l<<" Mobius is = "<<mobius(l)<<" the result from the sum is = "<<sum<<" and the overall sum is = "<<result<<endl;
   }
   return result;
}

mpfr::mpreal S4b_innerSum(const uint64_t x, const mpfr::mpreal u, const uint64_t l, const mpfr::mpreal psiOfU) {
   mpfr::mpreal sum = 0.0;
   const long double end = std::sqrt(x/l); //k <= sqrt(x/l), k is an integer...
   //std::cout << "S4b_innerSum about to begin with the following parameters:" << std::endl;
   //std::cout << "x: " << x << " u: " << u << " l: " << l << " psiOfU: " << psiOfU << " sum: " << sum << " end: " << end << std::endl;
   //std::cout << "Entering the loop now...";
   std::cout<<"  Bounds for k: 0 < k <= "<<end<<endl;
   for (uint64_t k = 1; k <= end; ++k) {
      const long long n = N(x, u, l, k);
      std::cout<<"    @k = "<<k<<" N = "<<n;
      if (n != 0) {
        std::cout<<" psi(k) = "<<primetools::calculatePsiLongDouble(k)<<" and the result is = "<<(primetools::calculatePsiLongDouble(k) - psiOfU)*n;
	       sum += (primetools::calculatePsiLongDouble(k) - psiOfU)*n;
      }
      std::cout<<endl;
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
  std::cout<<"psi(u) = "<<psi_of_u<<std::endl;
  mpfr::mpreal result = 0.0;
  for(uint64_t l = 1; l <= (uint64_t) u; ++l) { //floor was ok
    std::cout<<l<<" <= "<<(uint64_t)u<<endl;
    mpfr::mpreal sum = (mobius(l) * slowS4_inner(x, u, l, psi_of_u));
    result += sum;
    std::cout<<"At l = "<<l<<" Mobius is = "<<mobius(l)<<" the result from the sum is = "<<sum<<" and the overall sum is = "<<result<<endl;
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
  std::cout<<lowerBound<<" < m <= "<<upperBound<<endl;
  for(long long m = lowerBound; m <= upperBound; ++m) {
    long long innerTerm = floor(static_cast<long double>(x)/(static_cast<long double>(l) * static_cast<long double>(m)));
    mpfr::mpreal firstTerm = primetools::calculatePsiLongDouble(innerTerm);
    // std::cout<<"psi("<<innerTerm<<") = "<<firstTerm<<std::endl;
    result += (firstTerm - psiOfU);
    std::cout<<"  At m = "<<m<<" current psi is = "<<firstTerm<<" psi - psi(u) = "<<firstTerm - psiOfU<<endl;
  }
  std::cout<<"  Returning sum = "<<result<<std::endl;
  return result;
}
