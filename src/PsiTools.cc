#include "PsiTools.h"

std::vector<mpfr::mpreal> psiTable;

void setupEnvironment() {
  mpfr::mpreal::set_default_prec(192);
  std::cout << std::setprecision(58) << std::scientific; //33-36 //15-17 //octuple: \log_10{2^237} = 71.344
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
  bool isEmpty = true;
  // psiVector = new std::std::vector<mpfr::mpreal>;
  std::cout<<"seting up psi table...";
  while(inFile >> str) {
    isEmpty = false;
    psiTable.push_back(str);
  }
  if(isEmpty)
    psiTable.push_back(0.0);
std::cout<<"Done"<<std::endl;
}

mpfr::mpreal getSmallPsi(uint64_t x) {
  if(x < psiTable.size())
    return psiTable[x];
  else
    return primetools::calculatePsiLongDouble(x);
}

mpfr::mpreal psi(uint64_t x) {
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
  std::cout<<"u = "<<u<<std::endl;

  if (u < 1)
     u = 1;
  return S1(x, u) + S2(x, u) - S3(x, u) - fourthSummation(x, u);
}
