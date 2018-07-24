#ifndef S4REDO_H
#define S4REDO_H

#include <iostream>
#include <vector>
#include "N.h"
#include "mobius.h"
#include "mpreal.h"
#include "Environment.h"
#include "Primetools.h"
#include <initializer_list>

class Sum {
public:
	Sum();
	Sum(const Sum&);
	Sum(const mpfr::mpreal&, const mpfr::mpreal&);
	
	Sum& operator+= (const Sum&);
	Sum& operator+= (const mpfr::mpreal&);
	
	template<typename Y>
	Sum operator+ (const Y&);
	
	Sum& operator= (const Sum&);
	
	mpfr::mpreal get() const;
	
	private:
		mpfr::mpreal sum, error, temp;
		void neumaier(const mpfr::mpreal&);
};

mpfr::mpreal fourthSummation(const long long, const mpfr::mpreal&);

mpfr::mpreal innerFourthSummationOriginal(const long long, const mpfr::mpreal&, const long long, const mpfr::mpreal&, const long long);

mpfr::mpreal innerFourthSummationWithN(const long long, const mpfr::mpreal&, const long long, const mpfr::mpreal&, const long long);

#endif //S4REDO_H
