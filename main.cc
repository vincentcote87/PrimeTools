#include <iostream>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"

using std::cout;
using std::endl;

int main() {
  setupEnvironment();
  uint64_t x;
  while(true) {
    cin >> x;
    uint64_t u = floor(cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x))) - 0.5);
    if (u < 1)
      u = 1;
    // long long u1 = floor(pow(static_cast<long double>(x), (1.0L/3.0L)) * pow(log(log(static_cast<long double>(x))), (2.0L/3.0L)));
    // long double u2 = pow(static_cast<long double>(x), (1.0L/3.0L)) * pow(log(log(static_cast<long double>(x))), (2.0L/3.0L));
    // long double u3 = floor(pow(static_cast<long double>(x), (1.0L/3.0L)) * pow(log(log(static_cast<long double>(x))), (2.0L/3.0L)));
    // long double lh = pow(static_cast<long double>(x), (1.0L/3.0L));
    // long double ln = log(static_cast<long double>(x));
    // long double rh = cbrtl(pow(log(log(x)), 2));

    // cout<<"lh: " << lh<<endl;
    // cout<<"rh: " << rh<<endl;
    // cout<<"rhln: " << std::pow(log(ln), 0.5)<<endl;
    // cout<<"using cube root "<<cbrtl(pow(log(log(x)), 2))<<endl;
    // cout<<"lh * rh" << lh*rh<<endl;
    // if(u <= 0)
    //   u = 1;
    // cout<<primetools::calculatePsiLongDouble(x)<<endl;
    long double a = S4(x, u);
    long double b = slowS4(x, u);

    cout<<u<<endl;
    // cout<<u1<<endl;
    // cout<<u2<<endl;
    // cout<<u3<<endl;
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<a-b<<endl;
  }

  // cout<<slowS4(1000, 15)<<endl;
  // uint64_t a, b;
  // while (true) {
  //   cin>>a>>b;
  //   cout << "pow(a,b) = " << pow(a,b) << std::endl;
  // }
//   uint64_t x;
//   while (true) {
//     cin >> x;
//   cout<<"psi("<<x<<") = "<<psi(x)<<" aka " <<primetools::calculatePsiLongDouble(x) << endl;
//
// }
  // T(100);
  // uint64_t x = 100000000;
  // std::cout<<primetools::calculateTheta(0, x)<<std::endl;
  // std::cout<<primetools::calculatePsi(x)<<std::endl;
  // std::cout<<primetools::calculatePsi(x) - primetools::calculateTheta(x)<<std::endl;
// print_int_double(primetools::calculatePsi(100));
  // std::cout<<primetools::calculatePsi(x)<<std::endl;
  // std::cout<<primetools::calculatePsi(1000000000)<<std::endl;
  // std::cout<<primetools::calculatePsiNoTheta(x)<<std::endl;

  return 0;
}
