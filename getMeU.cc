#include <iostream>
#include <iomanip>
#include <mpreal.h>

int main() {
   mpfr::mpreal x, u;
   mpfr::mpreal::set_default_prec(512);
   std::cout << std::scientific << std::setprecision(155);
   mpfr::mpreal third = mpfr::mpreal{1.0} / mpfr::mpreal{3.0};
   while (true) {
      std::cin >> x;
      u = mpfr::pow(x, third, MPFR_RNDN) * mpfr::pow(mpfr::log(mpfr::log(x, MPFR_RNDN), MPFR_RNDN) * mpfr::log(mpfr::log(x, MPFR_RNDN), MPFR_RNDN), third, MPFR_RNDN);
      std::cout << "u: " << u << std::endl;
      std::cout << "x/u: " << x/u << std::endl;
   }
   return 0;
}
