#include <iostream>
#include "./include/Primetools.h"
#include "./include/int_double.h"

int main() {
  uint64_t x = 100000000;
  // std::cout<<primetools::calculateTheta(0, x)<<std::endl;
  // std::cout<<primetools::calculatePsi(x)<<std::endl;
  std::cout<<primetools::calculatePsi(x) - primetools::calculateTheta(x)<<std::endl;
// print_int_double(primetools::calculatePsi(100));
  return 0;
}
