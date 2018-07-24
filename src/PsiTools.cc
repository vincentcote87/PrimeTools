#include "PsiTools.h"

std::vector<mpfr::mpreal> psiTable;

void setupEnvironment() {
  mpfr::mpreal::set_default_prec(192);
  std::cout << std::setprecision(36) << std::scientific; //33-36 //15-17 //octuple: \log_10{2^237} = 71.344
  psi_setup();
  mobius_setup();
  std::cout<<"Precision set to "<<mpfr::mpreal::get_default_prec()<<std::endl;
}

void psi_setup() {
  // std::cout<<"seting up psi table...";
  // psiTable = new mpfr::mpreal[cutoff];
  // for (uint i = 0; i < cutoff; ++i) {
  //   psiTable[i] = 0;
  // }
  // std::cout<<"Done"<<std::endl;
  std::ifstream inFile;
  inFile.open("./psiList.txt");
  std::string str;
  // psiVector = new std::std::vector<mpfr::mpreal>;
  std::cout<<"seting up psi table...";
  while(inFile >> str) {
    psiTable.push_back(str);
  }
std::cout<<"Done"<<std::endl;
}

mpfr::mpreal psi(uint64_t x) {
  std::cout<<psiTable[2]<<std::endl;
  if (x < 2)
    return 0.0;
  if (x < psiTable.size()) {
    // if (psiTable[x] == 0.0) {
      // psiTable[x] = psi_work(x);
    // }
    return psiTable[x];
  }
  return psi_work(x);
}

mpfr::mpreal psi_work(uint64_t x) {
  if (x < 2)
    return 0.0;

  mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));

  if (u < 1)
     u = 1;
  return S1(x, u) + S2(x, u) - S3(x, u) - S4(x, u);
}
