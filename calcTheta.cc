#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"
#include "InterpretClock.h"
#include "bounds.h"
#include <exception>

int main(int argc, char* argv[]) {
  uint64_t x = 0;
  mpfr::mpreal psi = 0.0;
  setupEnvironment();

  maxK(2, 20);
  while(true) {
    std::cout<<"Enter value for x: ";
    std::cin>>x;
    // std::cout<<"Enter psi(x) (enter 0 if unknown): ";
    // std::cin>>psi;
    // psi = 1.0000000171997123225078042364104096062466623278281038116817e+13;
    // std::cout<<<<psi<<std::endl;
    std::cout<<"No Psi   = "<<primetools::calculateThetaLongDouble(1, x)<<std::endl;
    std::cout<<"With Psi = "<<primetools::calculateThetaWithPsi(x, 0)<<std::endl;
  }
  return 0;
}
