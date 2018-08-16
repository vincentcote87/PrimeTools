#include <iostream>
#include <iomanip>
#include <mpreal.h>
#include "HigherPsi.h"
#include "PsiTools.h"

int main(int argc, char* argv[]) {
   mpfr::mpreal::set_default_prec(192);
   std::cout << std::setprecision(58) << std::scientific;
   uint64_t x;
   if(argc == 2)
    x = std::stoll(argv[1]);
  else {
  	std::cout << "usage:\n     ";
    std::cout << argv[0] << " stoppoint" << std::endl;
    return 0;
  }
   for (uint64_t i = 0; i <= x; ++i) {
      if (higherPsi.walkK(i)) {
	 std::cout << i << ": " << higherPsi.sumThetas() << std::endl;
      }
   }
   return 0;
}
