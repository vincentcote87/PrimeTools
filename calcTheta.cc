#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"
#include "InterpretClock.h"
#include <exception>

int main(int argc, char* argv[]) {
  uint64_t x = 0;
  setupEnvironment();
  while(true) {
    std::cin>>x;
    std::cout<<primetools::calculateThetaLongDouble(1, x)<<std::endl;
  }
  return 0;
}
