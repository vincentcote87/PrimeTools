#include "many.h"

void fillMorePrimes(long long target) {
	if (target <= 0) {
		target = 1;
	}
	if (target <= prime.size())
		return;
	size_t i = prime.size();
	prime.resize(target);
	for (; i < prime.size(); ++i) {
		prime[i] = it.next_prime();
	}
}

unsigned long long integer_raise2(const unsigned long long b) {
	unsigned long long a = 1;
		a <<= b;
	return a;
}

//true if we walked
bool walkK(const long long x) {

	bool result = false;
	long double xNegK;
	long long pos = 0;
	for (long long i = 1; x >= integer_raise2(i); ++i) {
		 if (pos >= k.size()) {
	k.push_back(0.0);
	theta.push_back(0.0);
	cur.push_back(0);
	lastPrime.push_back(1);
		 }
		 xNegK = std::pow(x, 1.0/static_cast<long double>(i));
		 if (static_cast<long long>(k[pos]) < static_cast<long long>(xNegK)) {
			 k[pos] = xNegK;
	//std::cout << "lastPime" << lastPrime[pos] << std::endl;
			 while (lastPrime[pos] <= static_cast<long long>(xNegK)) {
				 result = true;
				 theta[pos] += log(mpfr::mpreal{lastPrime[pos]}, MPFR_RNDN);
				 if (cur[pos] >= prime.size())
					 fillMorePrimes(cur[pos] + 1);
				 lastPrime[pos] = prime[cur[pos]++];
			 }
	//std::cout << std::endl;
		 }
		 //std::cout << i << " --- " << xNegK << " --- " << theta[pos] << std::endl;
		 ++pos;
	}
	//  std::cout<<"In Walkk, theta size is "<<theta.size()<<std::endl;
	//  for(int i = 0; i < theta.size(); ++i) {
	// 	 std::cout<<"		theta("<<i<<") = "<<theta[i]<<std::endl;
	//  }
	return result;

}

bool walkKB(const long long x) {
	 bool result = false;
				while (lastPrimeB <= static_cast<long long>(x)) {
					result = true;
					thetaB += log(mpfr::mpreal{lastPrimeB}, MPFR_RNDN);
					// if (curB >= prime.size())
					// 	fillMorePrimes(curB + 1);
					// lastPrimeB = prime[curB++];
				}
	 return result;
}


mpfr::mpreal sumThetas() {
	mpfr::mpreal sum = 0.0;
	for (size_t i = 0; i < theta.size(); ++i) {
		sum += theta[i];
	}
	return sum;
}

mpfr::mpreal higherPsi(long long x) {
	if (x < 2)
		return 0.0;
	walkK(x);
	return sumThetas();
}

mpfr::mpreal higherTheta(long long x) {
	// std::cout<<"x = "<<x<<", in higherTheta...";
		if (x < 2)
		return 0.0;
	walkKB(x);
	// std::cout<<"Done"<<std::endl;
	return thetaB;
}
