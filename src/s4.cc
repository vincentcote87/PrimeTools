#include "s4.h"

Sum::Sum()
	: sum{0.0}, error{0.0}, temp{}
{}

Sum::Sum(const Sum& a)
	: sum{a.sum}, error{a.error}, temp{}
{}

Sum::Sum(const mpfr::mpreal& a, const mpfr::mpreal& b)
	: sum{a}, error{b}, temp{}
{}

void Sum::neumaier(const mpfr::mpreal& val) {
    temp = sum + val;
    if (abs(sum, MPFR_RNDN) >= abs(val, MPFR_RNDN)) {
      error += (sum - temp) + val;
    } else {
      error += (val - temp) + sum;
    }
    sum = temp;
}

mpfr::mpreal Sum::get() const {
	return sum + error;
}

Sum& Sum::operator+= (const Sum& a) {
	neumaier(a.get());
	return *this;
}

Sum& Sum::operator+= (const mpfr::mpreal& a) {
	neumaier(a);
	return *this;
}

template<typename Y>
Sum Sum::operator+ (const Y& a) {
	Sum b{*this};
	b += a;
	return b;
}

Sum& Sum::operator= (const Sum& a) {
	this->sum = a.sum;
	this->error = a.error;
	return *this;
}

mpfr::mpreal fourthSummation(const long long x, const mpfr::mpreal& u) {
	Sum A;
	for (long long l = 1; l <= u; ++l) {
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
		const mpfr::mpreal psiOfU = psi(u.toLLong(MPFR_RNDD));
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
		s += (psi(k) - psiOfU) * n;
	}
	return s.get();
}
