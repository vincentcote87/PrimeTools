#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"

using std::cout;
using std::endl;

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

  std::cout << std::setprecision(88) << std::scientific; //33-36 //15-17 //octuple: \log_10{2^237} = 71.344
  mpfr::mpreal::set_default_prec(384);
  //TO GENERATE PSI TABLE
  for(int x = 0; x < 1000000; ++x)
    std::cout<<primetools::calculatePsiLongDouble(x)<<std::endl;

  return 0;
}
