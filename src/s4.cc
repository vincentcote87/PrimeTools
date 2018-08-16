#include "s4.h"

Section::Section()
	: upper{}, l{}, mob{}
{}

Section::Section(const long long a, const long long b, const long long c)
	: upper{a}, l{b}, mob{c}
{}

bool Section::operator== (const Section& a) {
	if (upper == upper && l == l && mob == mob)
		return true;
	return false;
}

bool Section::operator< (const Section& a) {
	if (upper < a.upper)
		return true;
	if (upper > a.upper)
		return false;
	if (l < a.l)
		return true;
	if (l > a.l)
		return false;
	return mob < a.mob;
}

long long fillConsecutive(const long long start, const long long stop, HigherPsi& climber, Consecutive& spacer) {
   #ifdef DEBUG_STRANGES4
   std::cout << "S4: Replacing my personal table with" << (stop - start + 1) << "values from " << start << " to " << stop << "..." << std::flush;
   #endif //DEBUG_STRANGES4
   spacer.clear();
   spacer.push_back(climber(start));
   spacer.setOffset(start);
   for (long long i = start+1; i <= stop; ++i) {
      if (climber.walkK(i)) {
	 spacer.push_back(climber.sumThetas());
      } else {
	 spacer.tie_back();
      }
   }
   #ifdef DEBUG_STRANGES4
   std::cout << "Done" << std::endl;
   #endif //DEBUG_STRANGES4
}

mpfr::mpreal strangeS4(const long long x, const mpfr::mpreal& u, const long long space) {
   Sum A;
   const mpfr::mpreal psiOfU = psi(u.toLLong(MPFR_RNDD));
   HigherPsi climber;
   Consecutive spacer;
   const long long lower = 1;
   const long long upper = (mpfr::mpreal{x}/u).toLLong(MPFR_RNDD);
   const long long NLowerBound = 1;
   long long a = lower;
   #ifdef DEBUG_STRANGES4
   std::cout << "strangeS4: (initialization) x: " << x << std::endl;
   std::cout << "strangeS4: (initialization) u: " << u << std::endl;
   std::cout << "strangeS4: (initialization) psiOfU: " << psiOfU << std::endl;
   std::cout << "strangeS4: (initialization) lower: " << lower << std::endl;
   std::cout << "strangeS4: (initialization) upper: " << upper << std::endl;
   std::cout << "strangeS4: (initialization) NLowerBound: " << NLowerBound << std::endl;
   std::cout << "strangeS4: (initialization) a: " << a << std::endl;
   #endif //DEBUG_STRANGES4
   do {
      long long b = std::min(a + space, upper);
      #ifdef DEBUG_STRANGES4
      std::cout << "stangeS4: (" << a << ", " << b << ") " << std::endl;
      #endif //DEBUG_STRANGES4
      fillConsecutive(a, b, climber, spacer);
      for (long long l = u.toLLong(MPFR_RNDD); l >= 1; --l) {
	 const long long mob = mobius(l);
	 if (mob == 0)
	    continue;
	 const long long largeBound = (long long) (
	    static_cast<long double>(x)
	    /
	    (u.toLDouble(MPFR_RNDN) * static_cast<long double>(l))
	    );
	 const long long smallBound = (long long)
	    (sqrt(static_cast<long double>(x)/static_cast<long double>(l)));
	 const mpfr::mpreal mob_mpfr = mob;
	 #ifdef DEBUG_STRANGES4
	 std::cout << "strangeS4: largeBound: " << largeBound << " smallBound: " << smallBound << std::endl;
	 #endif //DEBUG_STRANGES4
	 if (largeBound < smallBound) {
	    A += mob_mpfr * strangeSummationOriginal(x, u, l, psiOfU, largeBound, a, b, spacer);
	 } else {
	    A += mob_mpfr * strangeSummationOriginal(x, u, l, psiOfU, smallBound, a, b, spacer);
	    A += mob_mpfr * strangeSummationWithN(x, u, l, psiOfU, std::max(NLowerBound, a), std::min(smallBound, b), spacer);
	 }
      }
      a = b + 1;
      #ifdef DEBUG_STRANGES4
      std::cout << "strangeS4: We just added to a = " << a << std::endl;
      #endif //DEBUG_STRANGES4
   } while (a <= upper);
   return A.get();
}


mpfr::mpreal strangeSummationOriginal(const long long x, const mpfr::mpreal& u, const long long l, const mpfr::mpreal& psiOfU, const long long upperBound, const long long force_low, const long long force_high, Consecutive& spacer) {
   Sum s;
   const long long beginning = ((long long) u.toLDouble(MPFR_RNDN)/static_cast<long double>(l)) + 1;
   long long temp;
   for (long long m = upperBound; m >= beginning; --m) {
      temp = x/(l*m);
      if (temp < force_low)
	 continue;
      if (temp > force_high)
	 break;
      s += spacer[temp] - psiOfU;
   }
   return s.get();
}

mpfr::mpreal strangeSummationWithN(const long long x, const mpfr::mpreal& u, const long long l, const mpfr::mpreal& psiOfU, const long long lowerBound, const long long upperBound, Consecutive& spacer) {
	Sum s;
	mpfr::mpreal n;
	for (long long k = lowerBound; k <= upperBound; ++k) {
	   n = N(x, u, l, k);
	   if (n == 0)
	      continue;
	   s += (spacer[k] - psiOfU) * n;
	}
	return s.get();
}

mpfr::mpreal fourthSummation(const long long x, const mpfr::mpreal& u) {
   Sum A;
   const mpfr::mpreal psiOfU = psi(u.toLLong(MPFR_RNDD));
   for (long long l = u.toLLong(MPFR_RNDD); l >= 1; --l) {
      const long long mob = mobius(l);
      if (mob == 0)
	 continue;
      const long long largeBound = (long long) (
	 static_cast<long double>(x)
	               /
	 (u.toLDouble(MPFR_RNDN) * static_cast<long double>(l))
	 );
      const long long smallBound = (long long)
	 (sqrt(static_cast<long double>(x)/static_cast<long double>(l)));
      const mpfr::mpreal mob_mpfr = mob;
      if (largeBound < smallBound) {
	 A += mob_mpfr * innerFourthSummationOriginal(x, u, l, psiOfU, largeBound);
      } else {
	 A += mob_mpfr * innerFourthSummationOriginal(x, u, l, psiOfU, smallBound);
	 A += mob_mpfr * innerFourthSummationWithN(x, u, l, psiOfU, smallBound);
      }
   }
   return A.get();
}

mpfr::mpreal innerFourthSummationOriginal(const long long x, const mpfr::mpreal& u, const long long l, const mpfr::mpreal& psiOfU, const long long upperBound) {
	const long long beginning = ((long long) u.toLDouble(MPFR_RNDN)/static_cast<long double>(l)) + 1;
	Sum s;
	for (long long m = upperBound; m >= beginning; --m) {
		s += psi(x/(l*m)) - psiOfU;
	}
	return s.get();
}

mpfr::mpreal innerFourthSummationWithN(const long long x, const mpfr::mpreal& u, const long long l, const mpfr::mpreal& psiOfU, const long long upperBound) {
	Sum s;
	mpfr::mpreal n;
	for (long long k = 1; k <= upperBound; ++k) {
	   n = N(x, u, l, k);
	   if (n == 0)
	      continue;
	   s += (psi(k) - psiOfU) * n;
	}
	return s.get();
}

long long calcUpper(const long long x, const mpfr::mpreal u, const long long l) {
   const mpfr::mpreal bound = mpfr::mpreal{x}/u;
   #ifdef DEBUG_ASCENDINGS4
   std::cout << "New Upper Bound: " << bound.toLLong(MPFR_RNDD);
   #endif //DEBUG_ASCENDINGS4
   return bound.toLLong(MPFR_RNDD);
} 



mpfr::mpreal ascendingS4(const long long x, const mpfr::mpreal& u, HigherPsi ascpsi) { //deliberate copying
   #ifdef DEBUG_ASCENDINGS4
   std::cout << "ascendingS4()***********************************************************************" << std::endl;
   #endif //DEBUG_ASCENDINGS4
   const mpfr::mpreal psiOfU = psi(u.toLLong(MPFR_RNDD));
   std::vector<Section> tablet;
   const long long lower = u.toLLong(MPFR_RNDD) + 1;
   #ifdef DEBUG_ASCENDINGS4
   std::cout << "lower bound: " << lower << std::endl;
   #endif //DEBUG_ASCENDINGS4
   for (long long l = 1; l <= u.toLLong(MPFR_RNDD); ++l) {
      const long long mob = mobius(l);
      switch (mob) {
	 case 1:
	 case -1:
	    tablet.push_back(Section{calcUpper(x, u, l), l, mob});
	    #ifdef DEBUG_ASCENDINGS4
	    std::cout << " with l: " << l << " and mob: " << mob << std::endl;
	    #endif //DEBUG_ASCENDINGS4
	 case 0: //ignore mobius(0) by not including that value of l in the sum
	    break;
      }
   }
   #ifdef DEBUG_ASCENDINGS4
   std::cout << "Items to consider in tablet: " << tablet.size() << std::endl;
   #endif //DEBUG_ASCENDINGS4
   Sum sum;
   long long count;
   for (long long lm = tablet[0].upper; lm >= lower; --lm) {
   #ifdef DEBUG_ASCENDINGS4
      std::cout << "Now doing lm = " << lm << " ";
   #endif //DEBUG_ASCENDINGS4
      count = 0;
      for (size_t i = 0; i < tablet.size() && lm <= tablet[i].upper; ++i) {
   #ifdef DEBUG_ASCENDINGS4
	 std::cout << "i: " << i << " tablet[i].upper: " << tablet[i].upper << " tablet[i].l: " << tablet[i].l << " tablet[i].mob: " << tablet[i].mob << " action: ";
   #endif //DEBUG_ASCENDINGS4
	 if (lm % tablet[i].l == 0) {
            #ifdef DEBUG_ASCENDINGS4
            std::cout << "add";
            #endif //DEBUG_ASCENDINGS4
	    count += tablet[i].mob;
	 }
   #ifdef DEBUG_ASCENDINGS4
	 std::cout << " *************** ";
   #endif //DEBUG_ASCENDINGS4
      }
   #ifdef DEBUG_ASCENDINGS4
      std::cout << "INNER COMPLETE" << std::endl;
      std::cout << "count was " << count << std::endl;
   #endif //DEBUG_ASCENDINGS4
      if (count == 0)
	 continue;
      sum += (ascpsi(x / lm) - psiOfU) * mpfr::mpreal{count};
   }
   #ifdef DEBUG_ASCENDINGS4
   std::cout << std::endl;
   std::cout << "***********************************************************************************" << std::endl;
   #endif //DEBUG_ASCENDINGS4
   return sum.get();
}
