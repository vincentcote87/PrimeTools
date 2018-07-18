#include "N.h"

integer N(const integer x, const mpfr::mpreal u, const integer l, const integer k) {
   assert(x < 10000000000000000);
   assert(l < 10000000000000000);
   const integer L2 = static_cast<integer>(x/(u.toLDouble(MPFR_RNDN) * static_cast<long double>(l))); //deliberate floor

   const auto roundEnv = std::fegetround();
   std::fesetround(FE_TONEAREST);
   const integer L1 = ((long long) std::sqrt(((long double) x)/((long double) l))) + 1; //deliberate floor of sqrt. can replace with a pure flooring integer sqrt later

   std::fesetround(roundEnv);
   const integer M2 = x/(l*k); //deliberate floor
   const integer M1 = (x/(l*(k+1))) + 1; //deliberate floor of division
   //if (M1 > M2)
      //return 0;
     //std::cout << "L1: " << L1 << "; L2: " << L2 << "; M1: " << M1 << "; M2: " << M2 << std::endl;
   const integer high = std::min(L2,M2);
   const integer low = std::max(L1,M1);


   if (high < low)
      return 0;


   return high - low + 1; //inclusive count of consecutive integers from low through high
}
