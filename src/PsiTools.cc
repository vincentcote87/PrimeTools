#include "PsiTools.h"

Consecutive psiTable;
std::map<uint64_t, mpfr::mpreal> psiMap;

//1024, 309
void setupEnvironment() {
  mpfr::mpreal::set_default_prec(512);
  std::cout << std::setprecision(155) << std::scientific; //33-36 //15-17 //octuple: \log_10{2^237} = 71.344
  psi_setup();
  mobius_setup();
  std::cout<<"Precision set to "<<mpfr::mpreal::get_default_prec()<<std::endl;
}

void psi_setup() {
  std::cout<<"seting up psi table..." << std::flush;
  std::cout << "nothing ";
  std::cout<<"Done"<<std::endl;
}

mpfr::mpreal psi(uint64_t x) {
   if (x < 2) {
      return 0.0;
   }
   if (x < psiTable.size()) {
      return psiTable[x];
   }
   std::cout << "psi() We are outside of the psiTable. Attempt to use psiMap for x = " << x << std::endl;
  if (psiMap[x] == 0.0) {
  	if (x < 100)
  		psiMap[x] = primetools::calculatePsiLongDouble(x);
  	else
  		psiMap[x] = psi_work(x);
  }
  return psiMap[x];
}

void expandPsiTable(long long target) {
   std::cout << "Now expanding the psiTable from " << psiTable.size() << " to " << target << "..." << std::flush;
   if (psiTable.size() == 0) { //note: this if statement fixes an issue that did not cause any issues (issue stems from walkK returning false for walkK(0))
      psiTable.push_back(mpfr::mpreal{0}); //psi(0)
      psiTable.tie_back(); //psi(1)
   }
   while (psiTable.size() < target) {
      if (walkK(psiTable.size())) { //faster than comparing mpfr
	 psiTable.push_back(sumThetas());
      } else {
	 psiTable.tie_back();
      }
   }
   std::cout << " unique values: " << psiTable.internalSize() << std::endl;
   psiMap.clear();
}

mpfr::mpreal psi_work(uint64_t x) {
  if (x < 2)
    return 0.0;
  mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
  if (u < 1)
     u = 1;
  if (psiTable.size() < x/u.toLLong(MPFR_RNDD))
  	expandPsiTable(x/u.toLLong(MPFR_RNDD));
  #ifdef VERBOSE_PSI
  std::cout<<"u = "<<u<<std::endl;
  #endif //VERBOSE_PSI
  mpfr::mpreal s1, s2, s3, s4;
  #ifdef VERBOSE_PSI
  std::cout << "Calculating Psi.." << std::flush;
  std::cout << '1' << std::flush;
  #endif //VERBOSE_PSI
  s1 = S1(x, u);
  #ifdef VERBOSE_PSI
  std::cout << '2' << std::flush;
  #endif //VERBOSE_PSI
  s2 = S2(x, u);
  #ifdef VERBOSE_PSI
  std::cout << '3' << std::flush;
  #endif //VERBOSE_PSI
  s3 = S3(x, u);
  #ifdef VERBOSE_PSI
  std::cout << '4' << std::flush;
  #endif //VERBOSE_PSI
  s4 = fourthSummation(x, u);
  #ifdef VERBOSE_PSI
  std::cout << "..done" << std::endl;
  #endif //VERBOSE_PSI
  return s1 + s2 - s3 - s4;
}
