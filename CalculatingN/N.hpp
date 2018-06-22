#ifndef N_HPP
#define N_HPP
#include <cassert>
#include <iostream>
#include <cmath>
#include <cassert>
#include <cfenv>
#include <algorithm>
typedef long long integer;
typedef long double rational;
integer N(const integer x, const integer u, const integer l, const integer k);
integer slowN(const integer x, const integer u, const integer l, const integer k);
#endif

integer N(const integer x, const integer u, const integer l, const integer k) {
   assert(x < 10000000000000000);
   assert(l < 10000000000000000);
   const integer L2 = x/(u*l); //deliberate floor
   const auto roundEnv = std::fegetround();
   std::fesetround(FE_TONEAREST);
   const integer L1 = ((long long) std::sqrt(((long double) x)/((long double) l))) + 1; //deliberate floor of sqrt. can replace with a pure flooring integer sqrt later
   std::fesetround(roundEnv);
   const integer M2 = x/(l*k); //deliberate floor
   const integer M1 = (x/(l*(k+1))) + 1; //deliberate floor of division
   if (M1 > M2)
      return 0;
   std::cout << "L1: " << L1 << "; L2: " << L2 << "; M1: " << M1 << "; M2: " << M2 << std::endl;
   const integer high = std::min(L2,M2);
   const integer low = std::max(L1,M1);
   if (high < low)
      return 0;
   return high - low;
}

integer slowN(const integer x, const integer u, const integer l, const integer k) {
   //Note: According to Deleglise and Rivat this can be done in constant time
   const integer upperBound = (x/l) + 1; //intentionally flooring x/l
   const integer lowerBound = x/(u*l); //intentionally flooring x/ul
   assert(lowerBound <= upperBound);
   integer count = 0;
   //std::cout << "GOT HERE\n";
   for (integer m = lowerBound; m <= upperBound; ++m) {
      if (m != 0 && x/(l*m) == k) //intentional flooring
      {
	 //std::cout << "m: " << m;
	 //std::cout << " yes ";
	 count += 1;
      }
   }
   //std::cout << "\n\n";
   //std::cout << "upperBound: " << upperBound << " lowerBound: " << lowerBound << std::endl;
   //std::cout << "gap: " << (upperBound - lowerBound) << " count: " << count << std::endl;
   return count;
}
