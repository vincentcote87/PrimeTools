#include <iostream>
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

int main(int argc, char* argv[]) {
  setupEnvironment();
  uint64_t x;
  if(argc == 2)
    x = std::stoll(argv[1]);

  // cout<<setprecision(22);
  // cout<<"w theta = "<<primetools::calculatePsiLongDouble(x)<<endl;
  // cout<<"without theta = "<<primetools::calculatePsiNoTheta(x)<<endl;
    // for(uint64_t i = 1; i <= 100000; ++i) {
    //   behaviour(i);
    // }
    // cout<<myArr[743]<<endl;
  // // while(true) {
  // //   cin >> x;
  // //   cout<<"new psi = "<<psi(x)<<" slow psi = "<<primetools::calculatePsiLongDouble(x)<<endl;

    // long double a = psi(x);
    // long double b = primetools::calculatePsiLongDouble(x);
    // cout<<"Formula   "<<a<<endl;
    // cout<<"Brute cal "<<b<<endl;
    // cout<<"Diffrence "<<a - b<<endl;
    long long u = floor(cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x))) - 0.5);
    cout<<"s4      = "<<S4(x, u)<<endl;
    cout<<"s4 slow = "<<slowS4(x, u)<<endl;

  return 0;
}
