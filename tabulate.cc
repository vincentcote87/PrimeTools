#include <iostream>
#include <iomanip>
#include <mpfr.h>
#include <cmath>
#include "PsiTable.h"

PsiTable table;

int main(int argc, char* argv[]) {
   mpfr::mpreal::set_default_prec(512);
   std::cout << std::scientific << std::setprecision(155);
   uint64_t x;
   if(argc == 2)
    x = std::stoll(argv[1]);
  else {
  	std::cout << "usage:\n     ";
    std::cout << argv[0] << " stoppoint" << std::endl;
    return 0;
  }
   table.tabulate(x);
   for (size_t i = 0 ; i < table.size(); ++i) {
      std::cout << "psi(" << i << ") = " << table[i] << std::endl;
   }
   return 0;
}
