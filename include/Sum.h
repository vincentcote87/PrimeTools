#ifndef SUM_H
#define SUM_H

#include <mpreal.h>

class Sum {
public:
	Sum();
	Sum(const Sum&);
	Sum(const mpfr::mpreal&, const mpfr::mpreal&);

	Sum& operator+= (const Sum&);
	Sum& operator+= (const mpfr::mpreal&);

	Sum& operator-= (const Sum&);
	Sum& operator-= (const mpfr::mpreal&);
	
	template<typename Y>
	Sum operator+ (const Y&);

	Sum& operator= (const Sum&);

	mpfr::mpreal get() const;

	private:
		mpfr::mpreal sum, error, temp;
		void neumaier(const mpfr::mpreal&);
};

#endif //SUM_H
