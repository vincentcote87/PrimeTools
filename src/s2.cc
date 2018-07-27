#include "s2.h"

mpfr::mpreal T(uint64_t n) {
	return fastT(n);
}

mpfr::mpreal fastT(uint64_t arg) {
	mp_prec_t def_prec = mpfr::mpreal::get_default_prec();
	mpfr::mpreal PI = {"3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105118548074462379962749567351885752724891227938183011949129833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132000568127145263560827785771342757789609173637178721468440901224953430146549585371050792279689258923"};
  mpfr::mpreal N = (mpfr::mpreal) arg;
  mpfr::mpreal T1 = 0.0;
  mpfr::mpreal T2 = 0.0;
  mpfr::mpreal T3 = 0.0;

  T1 = (N + mpfr::mpreal{0.5}) * log(N, MPFR_RNDN) - N;
  T2 = mpfr::mpreal{0.5} * log(mpfr::mpreal{2.0} * PI, MPFR_RNDN);
  for(int j = 1; j <= J; j++) {
  	//using 1 originally
    T3 += B2[j]/(mpfr::mpreal{(2*j)*(2*j-1)} * pow(N,mpfr::mpreal{2*j-1}, MPFR_RNDN)); // 1
  }

	mpfr::mpreal result = T1 + T2 + T3;
	mpfr::mpreal::set_default_prec(def_prec);
  return result;
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
