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
  std::chrono::steady_clock clk;
  if(argc == 2)
    x = std::stoll(argv[1]);
  else {
    x = 100;
    cout<<"default value of x set at "<<x<<endl;
  }

  mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));

  cout<<"S4*******************************************************************************"<<endl;
  mpfr::mpreal a = S4(x, u);
  cout<<endl<<endl<<"slowS4*******************************************************************************"<<endl;
  cout<<endl<<endl;
  mpfr::mpreal b = slowS4(x, u);
  cout<<"u         "<<u<<endl;
  cout<<"S4        "<<a<<endl;
  cout<<"Slow S4   "<<b<<endl;
  cout<<"Diffrence "<<a - b<<endl;

  return 0;
}
