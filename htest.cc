#include <iostream>
#include <string>
#include "mpreal.h"
#include "many.h"
#include "PsiTools.h"

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
  mpfr::mpreal valE = "2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901157383418793070215408914993488416750924476146066808226480016847741185374234544243710753907774499206955170276183860626133138458300075204493382656029760";
  bool pass = true;
  mpfr::mpreal d, h, r;
  mpfr::mpreal concern = "8.63616855509444462539e-78";
   for (uint64_t i = 0; i <= x; ++i) {
      d = primetools::calculatePsiLongDouble(i);
      h = higherPsi(i);
      r = abs(d - h, MPFR_RNDN) / d;
      if (r > concern) {
      	pass = false;
      	std::cout << "Failed on psi(" << i << ")\n";
      	std::cout << "Higher Psi:    " << h << '\n';
      	std::cout << "Theta Psi:     " << d << '\n';
      	std::cout << "Difference:    " << d - h << '\n';
      	std::cout << "Exp:           " << pow(abs(d-h, MPFR_RNDN), valE, MPFR_RNDN) << std::endl;
      }
   }
   if (pass)
   	std::cout << "All values pass" << std::endl;
   return 0;
}
