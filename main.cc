#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
// #include "N.hpp"

using std::cout;
using std::endl;

void interpretClk(const std::chrono::milliseconds& a) {
   long long count = a.count();
   const long long h = count / 3600000;
   count %= 3600000;
   const long long min = count / 60000;
   count %= 60000;
   const long long s = count / 1000;
   count %= 1000;
   const long long us = count;
   std::cout << "Ran for: " << h << ':' << min << ':' << s << ':' << us << std::endl;
}

int main(int argc, char* argv[]) {

  // setupEnvironment();
  uint64_t x;
  // std::chrono::steady_clock clk;
  if(argc == 2)
    x = std::stoll(argv[1]);

  // cout<<N(1000 , 15.52, 1, 14)<<endl;
    mpfr::mpreal::set_default_prec(120);
    // mpfr::mpreal realLD = 2.0;
    // mpfr::mpreal myReal = log(realLD, MPFR_RNDN);
    // long double myLog = 0.0;
    // myLog = primetools::log(x);
    // cout<<setprecision(33);
    // cout<<std::log(x)<<endl;
    // cout<<myReal<<endl;
    // cout<<mpfr::mpreal::get_default_prec()<<endl;
  cout<<setprecision(21);
  // cout<<"w theta = "<<primetools::calculatePsiLongDouble(x)<<endl;
  // cout<<"without theta = "<<primetools::calculatePsiNoTheta(x)<<endl;
    // for(uint64_t i = 1; i <= 100000; ++i) {
    //   behaviour(i);
    // }
    // cout<<myArr[743]<<endl;
  // // while(true) {
  // //   cin >> x;
  // //   cout<<"new psi = "<<psi(x)<<" slow psi = "<<primetools::calculatePsiLongDouble(x)<<endl;

    // mpfr::mpreal a = psi(x);
    mpfr::mpreal b = primetools::calculatePsiLongDouble(x);
    // cout<<"Formula   "<<a<<endl;
    cout<<"Brute cal "<<b<<endl;
    // cout<<"Diffrence "<<a - b<<endl;

    // cout<<N(10000, 3.666721582566334971392540964529871417e+01, 1, 36)<<endl;
    // cout<<bruteN(10000, 3.666721582566334971392540964529871417e+01, 1, 36)<<endl;

    // long double u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
    // cout<<"u       = "<<u<<endl;
    // cout<<"s4      = "<<S4(x, u)<<endl;
    // cout<<"s4 slow = "<<slowS4(x, u)<<endl;
    //
    // auto before = clk.now();
    // long double temp = psi(x);
    // std::cout << "psi:     " << temp << std::endl;
    // interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(clk.now() - before));
    // before = clk.now();
    // long double temp2 = primetools::calculatePsiLongDouble(x);
    // std::cout << "slowPsi: " << temp2 << std::endl;
    // interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(clk.now() - before));
    // cout << "psi - slowPsi = " << temp - temp2 << std::endl;
    // std::cout << std::endl;

  return 0;
}
