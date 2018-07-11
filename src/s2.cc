#include "s2.h"

void Tsetup(uint64_t x) {
	std::cout << "Running Tsetup...";
	mpfr::mpreal x_u = (mpfr::mpreal) (x);
	T_table = new mpfr::mpreal[x + 1];
	size_t oldSize = T_tableSize;
	T_tableSize = x + 1;
	mpfr::mpreal sum;
	if (oldSize) {
		sum = T_table[oldSize - 1];
	} else {
		sum = 0.0;
	}
	size_t index;
	if (oldSize) {
		index = oldSize;
	} else {
		index = 1;
	}
	for (mpfr::mpreal i = index; i <= x_u; ++i) {
		sum += log(i, MPFR_RNDN);
		T_table[index++] = sum;
	}
	std::cout << "Done" << std::endl;
}

size_t idealT_tableSize(uint64_t x) {
	return x;
}

mpfr::mpreal Tbrute(uint64_t n) {
	mpfr::mpreal sum = 0.0;
	mpfr::mpreal N = n;
	for (mpfr::mpreal i = 1; i <= N; ++i) {
		sum += log(i, MPFR_RNDN);
	}
	return sum;
}

mpfr::mpreal T(uint64_t n) {
	if (n >= T_tableSize || n < 1) {
		std::cout << "OUTSIDE OF BOUNDS OF THE TABLE OF SUMS OF LOGARITHMS" << std::endl;
		if (T_tableSize)
			std::cout << "This is despite running Tsetup...." << "n = " << n;
		else
			std::cout << "Because Tsetup has not been run...." << "n = " << n;
		std::cout << std::endl;
		return Tbrute(n);
	}
	return T_table[n];
}

mpfr::mpreal fastT(uint64_t arg) {
	mp_prec_t def_prec = mpfr::mpreal::get_default_prec();
	mpfr::mpreal::set_default_prec(1024);
  mpfr::mpreal N = (mpfr::mpreal) arg;
 // long long T1a;
  mpfr::mpreal T1 = 0.0;
  mpfr::mpreal T2 = 0.0;
  mpfr::mpreal T3 = 0.0;

  T1 = (N + mpfr::mpreal{0.5}) * log(N, MPFR_RNDN) - N;
  T2 = mpfr::mpreal{0.5} * log(mpfr::mpreal{2.0} * PI, MPFR_RNDN);

  for(int j = 1; j <= J; j++) {
  	//using 1 originally
    T3 += B2[j]/(mpfr::mpreal{(2*j)*(2*j-1)} * pow(N,mpfr::mpreal{2*j-1}, MPFR_RNDN)); // 1
    //T3 += B2[j]/(mpfr::mpreal{2*j*(2*j-1)} * pow(N,mpfr::mpreal{2*j-2}, MPFR_RNDN)); // 2 (order of mag worse)
  }
	
	mpfr::mpreal result = T1 + T2 + T3;
	mpfr::mpreal::set_default_prec(def_prec);
  return result;
}

mpfr::mpreal Terror(uint64_t N) {
	//std::cout << "N = " << N << std::endl;
	mpfr::mpreal f3 = pow(mpfr::mpreal{N}, mpfr::mpreal{2*J+1}, MPFR_RNDN);
	mpfr::mpreal f12 = (mpfr::mpreal) 4*(J*J+J);
	//std::cout << "f3 = " << f3 << std::endl;
	return abs(B2[J], MPFR_RNDN) / (f12 * f3);
}

mpfr::mpreal S2(const uint64_t x, const mpfr::mpreal u) {
  mpfr::mpreal S = 0.0;
  mpfr::mpreal mob;
  mpfr::mpreal directSum;
  #ifdef DEBUG_S2
  std::cout << "m from 1 through u = " << u << std::endl;
  #endif //DEBUG_S2
  for(uint64_t m = 1; m <= u; m++) {
    mob = mobius(m);
    #ifdef DEBUG_S2
    std::cout << " " << "m = " << m << " mobius(m) = " << mob << std::endl;
    #endif //DEBUG_S2
    if (mob == 0) {
      continue;
    }
    uint64_t S2b = x/m;
    #ifdef DEBUG_S2
    std::cout << " " << "S2b aka floor(x/m)= " << S2b;
    #endif //DEBUG_S2
    if(S2b > 100000) {
      #ifdef DEBUG_S2
    std::cout << "T(x/m aka S2b) * mobius(m) = " << mob * T(x/m);
    #endif //DEBUG_S2
      S += mob * T(S2b);
    }
    else {
      directSum = 0.0;
      for(uint64_t i = 1; i <= S2b; ++i)
        directSum += log((mpfr::mpreal) i, MPFR_RNDN);
      S += mob * directSum;
    }
    #ifdef DEBUG_S2
    std::cout << "directSum(1 through x/m) * mobius(m) = " << (directSum * mob);
    std::cout << " now S is " << S << std::endl;
    #endif //DEBUG_S2
  }
  return S;
}