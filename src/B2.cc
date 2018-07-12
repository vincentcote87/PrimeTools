#include "B2.h"

unsigned long long B2Class::size() const {
      return SIZE;
}
mpfr::mpreal B2Class::operator[] (const unsigned long long i) const {
  return bernoulli[i];
}

B2Class::B2Class() {
	mpfr_prec_t def_prec = mpfr::mpreal::get_default_prec();
	mpfr::mpreal::set_default_prec(1024);
	bernoulli = new mpfr::mpreal[SIZE];
	for (int i = 0; i < SIZE; ++i) {
		bernoulli[i] = mpfr::mpreal{numerator[i]} / mpfr::mpreal{denominator[i]};
	}
	mpfr::mpreal::set_default_prec(def_prec);
}

B2Class::~B2Class() {
	delete[] bernoulli;
}
