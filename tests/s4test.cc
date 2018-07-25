#include <iostream>
#include <chrono>
#include "Environment.h"
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"

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

using std::cout;
using std::endl;
typedef std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> ClockReading;

void interpretClk(const std::chrono::milliseconds& a) {
   long long count = a.count();
   const long long h = count / 3600000;
   count %= 3600000;
   const long long min = count / 60000;
   count %= 60000;
   const long long s = count / 1000;
   count %= 1000;
   const long long ms = count;
   std::cout << "Ran for: " << h << ':' << min << ':' << s << ':' << ms << std::endl;
}

void interpretClk(const std::chrono::steady_clock::duration dur) {
	interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(dur));
}

int main(int argc, char* argv[]) {

  setupEnvironment();
  uint64_t x;
  std::chrono::steady_clock clk;
  if(argc >= 2)
    x = std::stoll(argv[1]);
  else {
    x = 100;
    cout<<"default value of x set at "<<x<<endl;
  }

  mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
  // mpfr::mpreal u = argv[2];
  cout<<"S4*******************************************************************************"<<endl;
  mpfr::mpreal a = fourthSummation(x, u);
  cout<<endl<<endl<<"slowS4*******************************************************************************"<<endl;
  cout<<endl<<endl;
  mpfr::mpreal b = slowS4(x, u);
  cout<<"u         "<<u<<endl;
  cout<<"Suggest u "<<cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x))) << endl;
  cout<<"MPFR u    " << pow(static_cast<mpfr::mpreal>(x), "0.33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333", MPFR_RNDN) * pow(log(log((mpfr::mpreal) x, MPFR_RNDN), MPFR_RNDN)*log(log((mpfr::mpreal) x, MPFR_RNDN), MPFR_RNDN), "0.33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333", MPFR_RNDN) << std::endl;
  cout<<"S4        "<<a<<endl;
  cout<<"Slow S4   "<<b<<endl;
  cout<<"Diffrence "<<a - b<<endl;
  cout<<"exp = "<<exp(abs(a-b))<<endl;

  return 0;
}
