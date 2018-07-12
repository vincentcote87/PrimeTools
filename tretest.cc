#include "s2.h"
#include <iostream>

using namespace std;

mpfr::mpreal sumLog(uint64_t n) {
	mp_rnd_t mode = mpfr::mpreal::get_default_rnd();
	mpfr::mpreal result = 0.0;
	mpfr::mpreal down = 0.0;
	mpfr::mpreal up = 0.0;
	mpfr::mpreal::set_default_rnd(MPFR_RNDN);
	for (mpfr::mpreal i = 1; i <= n; ++i) {
		result += log(i);
	}
	std::cout << "sumLog near: " << result << std::endl;
	result = 0.0;
	down = 0.0;
	up = 0.0;
	mpfr::mpreal::set_default_rnd(MPFR_RNDD);
	for (mpfr::mpreal i = 1; i <= n; ++i) {
		result += log(i);
	}
	std::cout << "sumLog down: " << result << std::endl;
	result = 0.0;
	down = 0.0;
	up = 0.0;
	mpfr::mpreal::set_default_rnd(MPFR_RNDU);
	for (mpfr::mpreal i = 1; i <= n; ++i) {
		result += log(i);
	}
	std::cout << "sumLog up:   " << result << std::endl;
	mpfr::mpreal::set_default_rnd(mode);
	return result;
}

int main() {
	mpfr::mpreal::set_default_prec(1024);
	cout << scientific << setprecision(308);
	for (int i = 0; i < B2.size(); ++i) {
		std::cout << "Bernoulli " << i*2 << " = " << B2[i] << std::endl;
	}
	const uint64_t UNTIL = 1000000;
	Tsetup(UNTIL);
	cout << "\n\n";
	mpfr::mpreal temp;
	for (uint64_t n = 10; n <= UNTIL; n*=10) {
		std::cout << "J = " << J << std::endl;
		mpfr::mpreal ft = fastT(n);
		cout << "T(" << n << ") = " << ft << std::endl;
		cout << "T's error:      " << Terror(n) << std::endl;
		mpfr::mpreal observed = sumLog(n);
		cout << "Observed Error: " << abs(observed - ft) << std::endl;
		cout << "\n\n";
	}
	return 0;
}
