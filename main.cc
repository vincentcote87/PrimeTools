#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"

using std::cout;
using std::endl;

void behaviour(const uint64_t i) {
  const long double ans = primetools::calculatePsiLongDouble(i);
  if (i%10000 == 0)
          cout<<i<<" is done = "<<ans<<endl;
}

void interpretClk(const std::chrono::milliseconds& a) {
   long long count = a.count();
   const long long h = count / 3600000;
   count %= 3600000;
   const long long min = count / 60000;
   count %= 60000;
   const long long s = count / 1000;
   count %= 1000;
   const long long us = count;
   std::cout << "Ran for: " << h << ':' << min << ':' << s << ':' << us << std::endl;
}

int main() {
  setupEnvironment();
  uint64_t x;
  std::chrono::steady_clock clk;
  while (true) {
     cin >> x;
     auto before = clk.now();
     long double temp = psi(x);
     std::cout << "psi:     " << temp << std::endl;
     interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(clk.now() - before));
     before = clk.now();
     long double temp2 = primetools::calculatePsiLongDouble(x);
     std::cout << "slowPsi: " << temp2 << std::endl;
     interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(clk.now() - before));
     cout << "psi - slowPsi = " << temp - temp2 << std::endl;
     std::cout << std::endl;
  }

  return 0;
}
