#ifndef S4_H
#define S4_H

#include <iostream>
#include <vector>
#include "N.h"
#include "mobius.h"
#include "mpreal.h"
#include "Environment.h"
#include "Primetools.h"
#include "PsiTools.h"
#include "HigherPsi.h"
#include "Sum.h"
#include <mpreal.h>
#include <algorithm>

class Section {
	public:
		long long upper;
		long long l;
		long long mob;
		Section();
		Section(const long long a, const long long b, const long long c);
		bool operator== (const Section&);
	        bool operator< (const Section&);
};



mpfr::mpreal fourthSummation(const long long, const mpfr::mpreal&);
mpfr::mpreal innerFourthSummationOriginal(const long long, const mpfr::mpreal&, const long long, const mpfr::mpreal&, const long long);
mpfr::mpreal innerFourthSummationWithN(const long long, const mpfr::mpreal&, const long long, const mpfr::mpreal&, const long long);
long long calcUpper(const long long, const mpfr::mpreal, const long long);
mpfr::mpreal ascendingS4(const long long, const mpfr::mpreal&, HigherPsi);

long long fillConsecutive(const long long, const long long, HigherPsi& climber, Consecutive& spacer);
mpfr::mpreal strangeS4(const long long x, const mpfr::mpreal& u, const long long space = 1000);
mpfr::mpreal strangeSummationOriginal(const long long, const mpfr::mpreal&, const long long, const mpfr::mpreal&, const long long, const long long, const long long, Consecutive&);
mpfr::mpreal strangeSummationWithN(const long long, const mpfr::mpreal&, const long long, const mpfr::mpreal&, const long long, const long long, Consecutive&);

#endif //S4_H
