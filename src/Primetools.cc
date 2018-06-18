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
    y = log(prime) - errorTerm;
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

int_double primetools::logpOverp(uint64_t x) {

}

uint64_t primetools::getKValue(uint64_t x) {
	return floor((log(x)/log(2)));
}

uint64_t primetools::nextTheta(uint64_t x, double k) {
	return floor(pow(x, (1.0/k)));
}
