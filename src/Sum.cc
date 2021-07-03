#include "Sum.h"

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

Sum& Sum::operator-= (const Sum& a) {
   neumaier(-a.get());
   return *this;
}

Sum& Sum::operator-= (const mpfr::mpreal& a) {
   neumaier(-a);
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
