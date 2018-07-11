#include "PsiTools.h"

void setupEnvironment() {
  std::cout << std::setprecision(72) << std::scientific; //33-36 //15-17 //octuple: \log_10{2^237} = 71.344
  psi_setup();
  mobius_setup();
  mpfr::mpreal::set_default_prec(256);
}

void psi_setup() {
  std::cout<<"seting up psi table...";
  psiTable = new mpfr::mpreal[cutoff];
  for (uint i = 0; i < cutoff; ++i) {
    psiTable[i] = 0;
  }
  std::cout<<"Done"<<std::endl;
}

mpfr::mpreal psi(uint64_t x) {
  if (x < 2)
    return 0.0;
  if (x < cutoff) {
    if (psiTable[x] == 0.0) {
      psiTable[x] = psi_work(x);
    }
    return psiTable[x];
  }
  return psi_work(x);
}

mpfr::mpreal psi_work(uint64_t x) {
  if (x < 2)
    return 0.0;
  mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
  if (T_tableSize < idealT_tableSize(x))
  	Tsetup(x);
  if (u < 1)
     u = 1;
   return S1(x, u) + S2(x, u) - S3(x, u) - slowS4(x, u);
  //return S1(x, u) + S2(x, u) - S3(x, u) - S4(x, u);
}



