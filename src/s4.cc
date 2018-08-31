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


LMOB_ITEM::LMOB_ITEM(const std::pair<long long, long long>& a)
   : l{a.first}, mob{a.second}
{}

LMOB_ITEM::LMOB_ITEM(const long long a, const long long b)
   : l{a}, mob{b}
{}

void printConsecutive(Consecutive& table) {
   std::cout << "PRINT TABLE" << std::endl;
   std::cout << "from " << table.firstX() << " to " << table.size() << std::endl;
   for (long long i = table.firstX(); i < table.size(); ++i) {
      std::cout << "psi(" << i << ") = " << table[i] << std::endl;
   }
   std::cout << "END OF TABLE" << std::endl;
}

std::vector<mpfr::mpreal> peeker;
std::map<std::pair<long long, long long>, long long> seen;
mpfr::mpreal anotherS4(const long long x, const mpfr::mpreal& u) {
   const long long floorOfU = u.toLLong(MPFR_RNDD);
   peeker.clear();
   peeker.resize(floorOfU+1, 0.0);
   const mpfr::mpreal psiOfU = psi(floorOfU); //requires tabulation up to u, or it will become recursive (and find a way to work, but slower)
   std::vector<LMOB_ITEM> lmob; //We will traverse only the nonzero l's of the mobius function more than once, saving on the main time waste in not storing the whole table.
   for (long long l = 1; l <= floorOfU; ++l) {
      switch (mobius(l)) {
	 case 1:
	 case -1:
	    lmob.push_back(std::make_pair(l, mobius(l)));
	    break;
	 case 0:
	 default:
	    break;
      }
   }
   Sum A;
   HigherPsi climber;
   Consecutive spacer;
   const long long lower = 1; //lower through upper = the region of inputs to psi
   const long long upper = (mpfr::mpreal{x}/u).toLLong(MPFR_RNDD);
   long long previousA = -1; //ensure previousHighPlusOne is smal
   long long a = 1;
   long long b;
   do {
      b = std::min(a + floorOfU*8, upper);
      fillConsecutive(a, b, climber, spacer);
      //printConsecutive(spacer);
      for (LMOB_ITEM item : lmob) {
	 const long long l = item.l;
	 const long long previousHighPlusOne = div_floor(x, (    (l == 1 ? 1 : l - 1)*previousA    )) + 1; //I must use the previous l? Or the previous l actually used?
	 const long long ma_aka_high = div_floor(x, (l*a));
	 const long long mb_aka_low = div_ceil(x, (l*b));
	 const long long hard_low = (u/mpfr::mpreal{l}).toLLong(MPFR_RNDD) + 1; //first integer greater than u/l
	 const long long hard_high = (mpfr::mpreal{x}/(mpfr::mpreal{l}*u)).toLLong(MPFR_RNDD); // last integer less than or equal to x/(ul)
	 const long long low = previousA == -1 ? std::max(mb_aka_low, hard_low) : std::max(std::max(mb_aka_low, hard_low), previousHighPlusOne);
	 const long long high = std::min(ma_aka_high, hard_high);
	 std::cout << "a " << a << " b " << b << " l " << l << " prevHigh+1 " << previousHighPlusOne << " ma_aka_high " << ma_aka_high << " mb_aka_low " << mb_aka_low << " hard_low " << hard_low << " hard_high " << hard_high << " low " << low << " high " << high << std::endl;
	 if (item.mob == 1) {
	    A += anotherS4Inner(x, l, low, high, psiOfU, spacer);
	    peeker[l] += anotherS4Inner(x, l, low, high, psiOfU, spacer);
	 } else {
	    A -= anotherS4Inner(x, l, low, high, psiOfU, spacer);
	    peeker[l] -= anotherS4Inner(x, l, low, high, psiOfU, spacer);
	 }
      }
      previousA = a;
      a = b + 1;
   } while (a <= upper);
   return A.get();
}

mpfr::mpreal anotherS4Inner(const long long x, const long long l, const long long low, const long long high, const mpfr::mpreal& psiOfU, Consecutive& table) {
   Sum A;
   for (long long m = low; m <= high; ++m) {
      A += table[x/(l*m)] - psiOfU;
   }
   return A.get();
}



long long fillConsecutive(const long long start, const long long stop, HigherPsi& climber, Consecutive& spacer) {
   std::cout << "S4: Replacing my personal table with" << (stop - start + 1) << "values from " << start << " to " << stop << "..." << std::flush;
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
   std::cout << "Done" << std::endl;
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
	 if (mob == 0) {
	    std::cout << "a " << a << " b " << b << " l " << l << " SKIP" << std::endl;
	    continue;
	 }
	 const long long originalLowerBound = ((long long) u.toLDouble(MPFR_RNDN)/static_cast<long double>(l)) + 1;
	 const long long largeBound = (long long) (
	    static_cast<long double>(x)
	    /
	    (u.toLDouble(MPFR_RNDN) * static_cast<long double>(l))
	       );
	 const long long smallBound = (long long)
	    (sqrt(static_cast<long double>(x)/static_cast<long double>(l)));
	 const mpfr::mpreal mob_mpfr = mob;
	 const long long ma_aka_high = x/(l*a);
	 const long long mb_aka_low  = div_ceil(x, l*b);
	 ++seen[std::make_pair(a, b)];
	 std::cout << "a " << a << " b " << b << " l " << l << " originalLowerBound " << originalLowerBound << " largeBound " << largeBound << " smallBound " << smallBound << " mb_aka_low " << mb_aka_low << " ma_aka_high " << ma_aka_high << std::endl;
	 if (largeBound < smallBound) {
	    A += mob_mpfr * strangeSummationOriginal(x, u, l, psiOfU, std::max(mb_aka_low, originalLowerBound), std::min(ma_aka_high, largeBound), spacer);
	 } else {
	    A += mob_mpfr * strangeSummationOriginal(x, u, l, psiOfU, std::max(mb_aka_low, originalLowerBound), std::min(ma_aka_high, smallBound), spacer);
	    //A += mob_mpfr * strangeSummationWithN(x, u, l, psiOfU, std::max(NLowerBound, a), std::min(smallBound, b), spacer);
         }
	 
      }
      a = b + 1;
   } while (a <= upper);
   std::cout << "What bounds have we seen?" << std::endl;
   for (auto i : seen) {
      std::cout << '[' << i.first.first << ", " << i.first.second << "] was seen " << i.second << " times." << std::endl;
   }
   std::cout << "And those are the bounds." << std::endl;
   return A.get();
}

long long div_ceil(const long long a, const long long b) {
   return (a + b - 1) / b;
}

long long div_floor(const long long a, const long long b) {
   return a/b;
}

mpfr::mpreal strangeSummationOriginal(const long long x, const mpfr::mpreal& u, const long long l, const mpfr::mpreal& psiOfU, const long long lowerBound, const long long upperBound, Consecutive& spacer) {
   Sum s;
   #ifdef DEBUG_STRANGES4
   std::cout << "l " << l << " lowerBound " << lowerBound << " upperBound " << upperBound << std::endl;
   #endif //DEBUG_STRANGES4
   for (long long m = upperBound; m >= lowerBound; --m) {
      s += spacer[x/(l*m)] - psiOfU;
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
	 mpfr::mpreal NOUSE = 0.0;
   const mpfr::mpreal psiOfU = psi(u.toLLong(MPFR_RNDD));
   for (long long l = u.toLLong(MPFR_RNDD); l >= 1; --l) {
      const long long mob = mobius(l);
      if (mob == 0) {
	 //std::cout << "fourthSummation: l = " << l << " produced " << "0.000000000000000000000000000000e+00" << std::endl;
	 continue;
      }
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
      //std::cout << "fourthSummation: l = " << l << " produced " <<  (A.get() - NOUSE) << std::endl;
      NOUSE = A.get();
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



mpfr::mpreal endlessS4(const long long x, const mpfr::mpreal& u) {
   HigherPsi fakeTable;
   const mpfr::mpreal psiOfU = psi(u.toLLong(MPFR_RNDD));
   Sum s;
   //for h's less than or equal to the middle bound (h represents the possible lm from x/lm), the k (k represents the floor(x/lm)), nonzero k's become "sparse".
   const long long middleBound = ((mpfr::mpreal{1} + sqrt(mpfr::mpreal{1+4*x}, MPFR_RNDN)) / mpfr::mpreal{2}).toLLong(MPFR_RNDD);
   //for as middleBoundK, I want a value that can be used for the equivalent to a less than, but will appear as less than or equal to in code (less than x/middleBound)
   const long long middleBoundAsK = (mpfr::mpreal{2*x} / (mpfr::mpreal{1} + sqrt(mpfr::mpreal{1+4*x}))).toLLong(MPFR_RNDU) - 1;
   //const long long upperBound = (mpfr::mpreal{x}/u).toLLong(MPFR_RNDD); //less than or equal to (floor of division)
   //const long long upperBoundAsH = u.toLLong(MPFR_RNDD);
   for (long long k = 1; k <= middleBoundAsK; ++k) {
      long long sumOfF = 0;
      for (long long l = u.toLLong(MPFR_RNDD); l >= 1; --l) {
	 if (mobius(l) == 0)
	    continue;
	 sumOfF += mobius(l) * F(x, u, l, k);
      }
      if (sumOfF == 0)
	 continue;
      s += (fakeTable(k) - psiOfU) * sumOfF;
   }
   const long long smallestDenominator = u.toLLong(MPFR_RNDD);
   for (long long h = middleBound; h >= smallestDenominator; --h) {
      const long long k = x/h; //should never repeat because we are working where k's are "sparse"
      long long sumOfF = 0;
      for (long long l = u.toLLong(MPFR_RNDD); l >= 1; --l) {
	 if (mobius(l) == 0)
	    continue;
	 sumOfF += mobius(l) * F(x, u, l, k);
      }
      //std::cout << "h: " << h << " sumOfF: " << sumOfF << std::endl;
      if (sumOfF == 0)
	 continue;
      s += (fakeTable(k) - psiOfU) * sumOfF;
      }
   return s.get();
}

mpfr::mpreal denominatorS4(const long long x, const mpfr::mpreal& u) {
   HigherPsi fakeTable;
   const mpfr::mpreal psiOfU = psi(u.toLLong(MPFR_RNDD));
   const long long largeDenominator = (u*u).toLLong(MPFR_RNDD);
   const long long smallDenominator = u.toLLong(MPFR_RNDD);
   Sum s;
   long long lastK = -200;
   for (long long h = largeDenominator; h >= smallDenominator; --h) {
      const long long k = x/h;
      if (k == lastK)
	 continue;
      lastK = k;
      long long sumOfF = 0;
      for (long long l = h; l >= 1; --l) {
	 //std::cout << "x: " << x << " u: " << u << " l: " << l << " k: " << k;
	 //std::cout << " mob: " << mobius(l) << " F: " << F(x, u, l, k) << std::endl;
	 if (mobius(l) == 0)
	    continue;
	 sumOfF += mobius(l) * F(x, u, l, k);
	 
      }
      //std::cout << "sumOfF: " << sumOfF << " k: " << k << " h: " << h << std::endl;
      if (sumOfF == 0)
	 continue;
      s += (fakeTable(k) - psiOfU) * sumOfF;
   }
   return s.get();
}
