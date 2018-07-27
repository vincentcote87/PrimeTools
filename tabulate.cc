#include <iostream>
#include "PsiTools.h"
#include "InterpretClock.h"

int main(int argc, char* argv[]) {
   setupEnvironment();
   std::chrono::steady_clock clk;
   uint64_t x;
   if(argc == 2)
    x = std::stoll(argv[1]);
  else {
    x = 100;
    cout<<"default value of x set at "<<x<<endl;
  }
   std::cout << "The default precision was: " << mpfr::mpreal::get_default_prec() << std::endl;
   std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> began, cur, here;
   began = clk.now();
   for (uint64_t i = 0; i < x; ++i) {
      cur = clk.now();
      std::cout << psi_work(i) << " *** Psi(" << i << ") ";
      here = clk.now();
      interpretClk(here - cur);
   }
   std::cout << "All Done!" << std::endl;
   std::cout << "Total Time: ";
   interpretClk(here - began);
   return 0;
}
