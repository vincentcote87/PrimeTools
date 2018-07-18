#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"

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
  // long long x;
  std::chrono::steady_clock clk;
  if(argc >= 2)
    x = std::stoll(argv[1]);
  else {
    x = 100;
    cout<<"default value of x set at "<<x<<endl;
  }

  // cout<<N(100, 2, 2, 3)<<endl;
  // cout<<slowN(100, 2, 2, 3)<<endl;

  // for(long long x = 2; x < y; ++x) {
  //   mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
  //   for(long long l = 1; l <= (long long)u; ++l) {
  //     for(long long k = 1; k <= floor(std::sqrt(x/l)); ++k) {
  //       if(N(x, u, l, k) != slowN(x, u, l, k)) {
  //         cout<<"MISMATCH x = "<<x<<" u = "<<u<<" l = "<<l<<" k = "<<k<<" N = "<<N(x, u, l, k)<<" and slowN = "<<slowN(x, u, l, k)<<endl;
  //       }
  //     }
  //   }
  // }

  mpfr::mpreal u = (cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)))) / 2.0;
  // mpfr::mpreal u = argv[2];
  #ifdef DEBUG_S4;
  cout<<"S4*******************************************************************************"<<endl;
  #endif;
  mpfr::mpreal a = S4(x, u);
  #ifdef DEBUG_S4;
  cout<<endl<<endl<<"slowS4*******************************************************************************"<<endl;
  #endif;
  cout<<endl<<endl;
  mpfr::mpreal b = slowS4(x, u);
  cout<<"u         "<<u<<endl;
  cout<<"Suggest u "<<cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x))) << endl;
  cout<<"MPFR u    " << pow(static_cast<mpfr::mpreal>(x), "0.33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333", MPFR_RNDN) * pow(log(log((mpfr::mpreal) x, MPFR_RNDN), MPFR_RNDN)*log(log((mpfr::mpreal) x, MPFR_RNDN), MPFR_RNDN), "0.33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333", MPFR_RNDN) << std::endl<<std::endl;
  cout<<"S4        "<<a<<endl;
  cout<<"Slow S4   "<<b<<endl;
  cout<<"Diffrence "<<a - b<<endl<<endl;
  cout<<"exp = "<<exp(abs(a-b))<<endl;

  return 0;
}
