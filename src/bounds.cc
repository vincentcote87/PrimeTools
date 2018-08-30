#include "bounds.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <mpreal.h>
#include "InterpretClock.h"

std::vector<mpfr::mpreal> maxK(const uint64_t lowerBound, const uint64_t upperBound){
	return maxK(lowerBound, upperBound, 0.0);
}

std::vector<mpfr::mpreal> maxK(const uint64_t lowerBound, const uint64_t upperBound, const mpfr::mpreal givenPsi){
	vector<mpfr::mpreal> M;
	uint64_t n = upperBound;
	mpfr::mpreal theta = 0.0;
	mpfr::mpreal logOfp = 0.0;
	mpfr::mpreal result = 0.0;
	long long upperK = 6;

	primesieve::iterator it;
	cout<<"Finding lowerbound prime...";
	it.skipto(lowerBound);
	cout<<"Done"<<endl;
	uint64_t Pn = it.next_prime();
	uint64_t PnPlusOne = it.next_prime();
	cout<<"Calculating theta with psi...";
	theta = primetools::calculateThetaWithPsi(lowerBound, givenPsi);
	theta += mpfr::log(Pn, MPFR_RNDN);
	cout<<"Done theta("<<Pn<<") = "<<theta<<endl;

	M.resize(upperK * 2, 0.0);

	mpfr::mpreal mpPn;
	mpfr::mpreal mpPnPlusOne;
	mpfr::mpreal mpK;

	for (; Pn <= n; PnPlusOne = it.next_prime()) {
		mpPn = Pn;
		mpPnPlusOne = PnPlusOne;
		theta += mpfr::log(mpPnPlusOne, MPFR_RNDN);
		logOfp = mpfr::log(mpPn);
		for(long long k = 0; k < upperK; ++k) {
			mpK = k;
			result = ((mpPn - theta) * mpfr::pow(logOfp, mpK, MPFR_RNDN)) / mpPn;
			if(result > M[k]){
				M[k] = result;
				M[k+upperK] = Pn; //the prime associated with max
			}
		}
		Pn = PnPlusOne;
	}
	return M;
}
