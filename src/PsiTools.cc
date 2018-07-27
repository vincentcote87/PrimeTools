#include "PsiTools.h"

std::vector<mpfr::mpreal> psiTable;
std::map<uint64_t, mpfr::mpreal> psiMap;

void setupEnvironment() {
  mpfr::mpreal::set_default_prec(1024);
  std::cout << std::setprecision(309) << std::scientific; //33-36 //15-17 //octuple: \log_10{2^237} = 71.344
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
  inFile.close();
std::cout<<"Done"<<std::endl;
}

/*mpfr::mpreal getSmallPsi(uint64_t x) {
  if(x < psiTable.size()) {
    return psiTable[x];
    }
  else {
    return primetools::calculatePsiLongDouble(x);
    }
}*/

mpfr::mpreal psi(uint64_t x) {
  if (x < 2)
     return 0.0;
  if (x < psiTable.size())
  	return psiTable[x];
  if (psiMap[x] == 0.0) {
  	if (x < 100000000)
  		psiMap[x] = primetools::calculatePsiLongDouble(x);
  	else
  		psiMap[x] = psi_work(x);
  }
  return psiMap[x];
}

mpfr::mpreal psi_work(uint64_t x) {
  if (x < 2)
    return 0.0;
  mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
  if (u < 1)
     u = 1;
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
