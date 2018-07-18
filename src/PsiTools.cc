#include "PsiTools.h"

std::vector<mpfr::mpreal> psiVector;

void setupEnvironment() {
  std::cout << std::setprecision(36) << std::scientific; //33-36 //15-17 //octuple: \log_10{2^237} = 71.344
  psi_setup();
  mobius_setup();
  mpfr::mpreal::set_default_prec(128);
  std::cout<<"Precision set to "<<mpfr::mpreal::get_default_prec()<<std::endl;
}

void psi_setup() {

  std::ifstream inFile;
  inFile.open("./psiList.txt");
  std::string str;
  // psiVector = new std::std::vector<mpfr::mpreal>;
  std::cout<<"seting up psi table...";
  while(inFile >> str) {
    psiVector.push_back(str);
  }
  std::cout<<"Done"<<std::endl;

  // std::cout<<psiVector.size()<<std::endl;
  // for(int i = 0; i < 20; ++i) {
  //   std::cout<<psiVector[i]<<std::endl;
  // }


  // std::cout<<"seting up psi table...";
  // psiTable = new mpfr::mpreal[cutoff];
  // for (uint i = 0; i < cutoff; ++i) {
  //   psiTable[i] = 0;
  // }
  // std::cout<<"Done"<<std::endl;
}

mpfr::mpreal psi(uint64_t x) {
  if(x < psiVector.size()) {
    return psiVector[x];
  }
  else {
    return psi_work(x);
  }

//   if (x < 2)
//     return 0.0;
//   if (x < cutoff) {
//     if (psiTable[x] == 0.0) {
//       psiTable[x] = psi_work(x);
//     }
//     return psiTable[x];
//   }
//   return psi_work(x);
}

mpfr::mpreal psiTable(long long x) {
  if(x < psiVector.size()) {
    return psiVector[x];
  }
  else {
    return primetools::calculatePsiLongDouble(x);
  }
}

mpfr::mpreal psi_work(uint64_t x) {
  if (x < 2)
    return 0.0;
  mpfr::mpreal u = (cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)))) / 2.0;
//  if (T_tableSize < idealT_tableSize(x))
 // 	Tsetup(x);
  if (u < 1)
     u = 1;
   // return S1(x, u) + S2(x, u) - S3(x, u) - slowS4(x, u);
   // mpfr::mpreal partial = S1(x, u) + S2(x, u) - S3(x, u);
   // mpfr::mpreal a = partial+slowS4(x, u);
   // mpfr::mpreal b = partial+S4(x, u);
   // std::cout<<"slowS4 "<<a<<std::endl;
   // std::cout<<"S4     "<<b<<std::endl;
   // std::cout<<"diff   "<<a - b<<std::endl<<std::endl;
  return S1(x, u) + S2(x, u) - S3(x, u) - S4(x, u);
  // return 1;
}
