#include <iostream>
#include "PsiTools.h"
#include "many.h"

int main(int argc, char* argv[]) {
   setupEnvironment();
   uint64_t x;
   if(argc == 2)
    x = std::stoll(argv[1]);
  else {
  	std::cout << "usage:\n     ";
    std::cout << argv[0] << " stoppoint" << std::endl;
    return 0;
  }
   for (uint64_t i = 0; i <= x; ++i) {
      std::cout << higherPsi(i) << std::endl;
   }
   return 0;
}
