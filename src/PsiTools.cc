#include "PsiTools.h"

void setupEnvironment() {
  std::cout << std::setprecision(36) << std::scientific;
  psi_setup();
  mobius_setup();
}

// const uint64_t mobiusCutoff = 3000000;
// long long *mobiusTable;
void mobius_setup() {
  mobiusTable = new long long[mobiusCutoff];
  for (uint i = 0; i < mobiusCutoff; ++i) {
    mobiusTable[i] = -2000;
  }
}

// const size_t cutoff = 10000000; //4294967295
// long double *psiTable;

void psi_setup() {
  psiTable = new long double[cutoff];
  for (uint i = 0; i < cutoff; ++i) {
    psiTable[i] = 0;
  }
}

long double psi(uint64_t x) {
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

long double psi_work(uint64_t x) {
  uint64_t u = floor(pow(x, (1.0/3.0)) * pow(log(log(x)), (2.0/3.0)));
  return S1(x, u) + S2(x, u) - S3(x, u) - slowS4(x, u);
  // return S1(x, u) + S2(x, u) - S3(x, u) - S4(x, u);
}

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

long double S1(uint64_t x, uint64_t u) {
  return primetools::calculatePsiLongDouble(static_cast<uint64_t>(u));
}
long double S2(uint64_t x, uint64_t u) {
  long double S = 0.0;
  uint64_t S2b = 0;

  for(uint m = 1; m <= u; m++) {
    S2b = x/m;
    long double sum = 0.0;
    if(S2b > 100000)
    // if(true)
      S += static_cast<long double>(mobius(m)) * T(x/m);
    else {
      for(uint i = 1; i <= S2b; ++i)
        sum += log(i);
      S += static_cast<long double>(mobius(m)) * sum;
    }
  }

  return S;
}

uint64_t pow(uint64_t a, uint64_t b) {
   if (b == 0)
      return 1;
   if (b == 1)
      return a;
   const uint64_t half = pow(a, b/2);
   if (b%2)
      return half*half;
   return half*half*a;
}

long long S3_B(const uint64_t x, const uint64_t u, const uint64_t p, const uint64_t l) {
  long long result = 0;
  const uint64_t L = (uint64_t) (log((long double) u)/log((long double) p)); //intentional floor
  for (uint64_t k = 1; k <= L; ++k) {
    result += x / (l * pow( p, k)); //intentional floor
  }
  // std::cout<< " result from S3_B = "<<result<<std::endl;
  return result;
}

long double S3_A(const uint64_t x, const uint64_t u, const uint64_t p) {
  long double S = 0.0;
  // uint64_t tmpMu = 0;
  for (uint64_t l = 1; l <= u; ++l) {
    S += mobius(l)*S3_B(x, u, p, l);
    // tmpMu += mobius(l);
    // std::cout<<tmpMu<<std::endl;
  }
  return S;
}

long double S3(const uint64_t x, const uint64_t u) {
  long double S = 0.0;

  primesieve::iterator it;
  it.skipto(0);
  uint64_t prime = it.next_prime();

  for (; prime <= u; prime = it.next_prime()) {
    S += log(prime)*S3_A(x, u, prime);
    // std::cout<<S<<std::endl;
  }
  // std::cout<<u<<std::endl;
  return S;
}
long double S4(uint64_t x, uint64_t u) {
  long double psi_of_u = primetools::calculatePsiLongDouble(u);
  return S4a(x, u, psi_of_u) + S4b(x, u, psi_of_u);
}

long double S4a(uint64_t x, uint64_t u, long double psiOfU) {
  long double result = 0.0;
  for(uint64_t l = 1; l <= u; ++l) {
    result += mobius(l) * S4a_innerLoop(x, u, l, psiOfU);
  }
  return result;
}

long double S4a_innerLoop(uint64_t x, uint64_t u, uint64_t l, long double psiOfU) {
  long double result = 0.0;
  uint64_t lowerM = u/l;
  uint64_t upperM = sqrt(x/l);
  for(uint64_t m = lowerM + 1; m <= upperM; ++m) {
    result += (primetools::calculatePsiLongDouble(x/(l * m)) - psiOfU);
  }
  return result;
}

long double S4b(uint64_t x, uint64_t u, const long double psiOfU) {
   long double sum = 0.0;
   for (uint64_t l = 1; l <= u; ++l) {
      sum += mobius(l)*S4b_innerSum(x, u, l, psiOfU);
   }
   return sum;
}

long double S4b_innerSum(const uint64_t x , const uint64_t u, const uint64_t l, const long double psiOfU) {
   long double sum = 0.0;
   const long double end = std::sqrt(x/l); //k <= sqrt(x/l), k is an integer...
   for (uint64_t k = 1; k <= end; ++k) {
      const long long n = N(x, u, l, k);
      if (n != 0) {
	 sum += (primetools::calculatePsiLongDouble(k) - psiOfU)*n;
      }
   }
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

long double slowS4(uint64_t x, uint64_t u) {
  long double psi_of_u = primetools::calculatePsiLongDouble(u);
  long double result = 0.0;
  for(uint64_t l = 1; l <= u; ++l) {
    result += mobius(l) * slowS4_inner(x, u, l, psi_of_u);
  }
  return result;
}

long double slowS4_inner(uint64_t x, uint64_t u, uint64_t l, long double psiOfU) {
  long double result = 0.0;
  uint64_t uOverl = u/l;
  uint64_t xOverul = x/(u * l);
  for(uint64_t m = uOverl + 1; m <= xOverul; ++m) {
    result += (primetools::calculatePsiLongDouble(x/(l * m)) - psiOfU);
  }
  return result;
}
