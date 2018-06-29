#include "../include/Primetools.h"


int64_t primetools::getPi(int64_t x) {
  return primecount::pi(x);
}

int_double primetools::calculateTheta(uint64_t x) {
  return primetools::calculateTheta(0, x);
}

int_double primetools::calculateTheta(uint64_t start, uint64_t stop) {
  int_double theta = 0.0;
	int_double temp = 0.0;
	int_double y = 0.0;
	int_double errorTerm = 0.0;

  primesieve::iterator it;
  it.skipto(start);
  uint64_t prime = it.next_prime();

  for (; prime <= stop; prime = it.next_prime()) {
    y = primetools::log(prime) - errorTerm;
    temp = theta + y;
    errorTerm = (temp - theta) - y;
    theta = temp;
  }

  return theta;
}

long double primetools::calculateThetaLongDouble(uint64_t start, uint64_t stop) {
  long double theta = 0.0;
	long double temp = 0.0;
	long double y = 0.0;
	long double errorTerm = 0.0;

  primesieve::iterator it;
  it.skipto(start);
  uint64_t prime = it.next_prime();

  for (; prime <= stop; prime = it.next_prime()) {
    y = primetools::log(prime) - errorTerm;
    temp = theta + y;
    errorTerm = (temp - theta) - y;
    theta = temp;
  }

  return theta;
}

int_double primetools::calculatePsi(uint64_t x) {
  int_double psi = 0.0;
  uint64_t k = primetools::getKValue(x);
  uint64_t tmpX = primetools::nextTheta(x, k);

	while(k > 0) {
		psi += primetools::calculateTheta(0, tmpX);
		tmpX = primetools::nextTheta(x, --k);
	}
  return psi;
}

long double primetools::calculatePsiLongDouble(uint64_t x) {
  long double psi = 0.0;
  if(x < 2)
    return psi;
  uint64_t k = primetools::getKValue(x);
  uint64_t tmpX = primetools::nextTheta(x, k);

	while(k > 0) {
		psi += primetools::calculateThetaLongDouble(0, tmpX);
		tmpX = primetools::nextTheta(x, --k);
	}
  return psi;
}

long double primetools::calculatePsiNoTheta(uint64_t x) {
  long double psi = 0.0;
	long double temp = 0.0;
	long double y = 0.0;
	long double errorTerm = 0.0;

  primesieve::iterator it;
  it.skipto(0);
  uint64_t prime = it.next_prime();
  for (; prime <= x; prime = it.next_prime()) {
    const long double logOfPrime = primetools::log(prime);
    const long double k = floor(primetools::log(x)/logOfPrime);
    y = (logOfPrime * k) - errorTerm;
    temp = psi + y;
    errorTerm = (temp - psi) - y;
    psi = temp;

  }
  return psi;
}



long double primetools::log(long double a, int digits) {

  mpfr_t ld_mpfr, result_mpfr;
  long double result = 0.0;
  mpfr_init2(ld_mpfr, digits);
  mpfr_init2(result_mpfr, digits);
  mpfr_set_ld(ld_mpfr, a, MPFR_RNDN);
  mpfr_log(result_mpfr, ld_mpfr, MPFR_RNDN);
  result = mpfr_get_ld(result_mpfr, MPFR_RNDN);
  mpfr_out_str (stdout, 10, 0, result_mpfr, MPFR_RNDN);
  putchar('\n');
  mpfr_clear(ld_mpfr);
  mpfr_clear(result_mpfr);
  return result;
  // long double low, high;
  // mpfr_t down, up, down_temp, up_temp;
  // mpfr_init2(down, digits);
  // mpfr_init2(up, digits);
  // mpfr_init2(down_temp, digits);mpfr_init2(up_temp, digits);
  // mpfr_set_ld(down, a, MPFR_RNDN);
  // mpfr_set_ld(up, a, MPFR_RNDN);
  // mpfr_log(down_temp, down, MPFR_RNDN);
  // low = mpfr_get_ld(down_temp, MPFR_RNDN);
  // mpfr_log(up_temp, up, MPFR_RNDN);
  // high = mpfr_get_ld(up_temp, MPFR_RNDN);
  //
  // mpfr_out_str(stdout, 10, 0, down, MPFR_RNDN);
  // cout << endl<< low <<endl;;
  //
  // mpfr_clear(down);
  // mpfr_clear(up);
  // mpfr_clear(down_temp);
  // mpfr_clear(up_temp);
  // return low;
}

int_double primetools::logpOverp(uint64_t x) {
  return -1.0;
}

uint64_t primetools::getKValue(uint64_t x) {
	return floor((primetools::log(x)/log(2)));
}

uint64_t primetools::nextTheta(uint64_t x, long double k) {
	return floor(pow(x, (1.0/k)));
}
