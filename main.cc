#include <iostream>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"

using std::cout;
using std::endl;

int main() {
  setupEnvironment();
  // cout<<S4(1000000, 190)<<endl;
  // cout<<slowS4(1000000, 190)<<endl;
  uint64_t x;
  while (true) {
    cin >> x;
  cout<<"psi("<<x<<") = "<<psi(x)<<" aka " <<primetools::calculatePsiLongDouble(x) << endl;

}
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
