#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"

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
   const long long ms = count;
   std::cout << "Ran for: " << h << ':' << min << ':' << s << ':' << ms << std::endl;
}

void interpretClk(const std::chrono::steady_clock::duration dur) {
	interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(dur));
}

int main(int argc, char* argv[]) {

  setupEnvironment();
  uint64_t x;
  std::chrono::steady_clock clk;
  if(argc == 2)
    x = std::stoll(argv[1]);
  else {
    x = 100;
    cout<<"default value of x set at "<<x<<endl;
  }
  while(true) {
    std::cout<<"Psi("<<x<<") = "<<primetools::calculatePsiLongDouble(x)<<endl;
    std::cin>>x;
  }
  // mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
  //
	// std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> p1, p2, p3, p4;
  //
	// p1 = clk.now();
	// mpfr::mpreal ans = primetools::calculatePsiNoTheta(x);
	// p2 = clk.now();
	// mpfr::mpreal an2 = primetools::calculatePsiLongDouble(x);
	// p3 = clk.now();
	// mpfr::mpreal an3 = psi(x);
  // // mpfr::mpreal an3 = 2.0;
	// p4 = clk.now();
	// std::cout << "Powered Psi: " << ans << std::endl;
	// std::cout << "Theta Psi:   " << an2 << std::endl;
	// std::cout << "A Psi:       " << an3 << std::endl;
  //
	// std::cout << "Powered Psi: ";
	// interpretClk(p2 - p1);
	// std::cout << "Theta Psi:   ";
	// interpretClk(p3 - p2);
	// std::cout << "A Psi:       ";
	// interpretClk(p4 - p3);

//  cout << "S2********************************************************************************" << endl;
 // mpfr::mpreal S2_result = S2(x, u);
  //cout << "S2 DONE **************************************************************************" << endl;
//  cout << "\n\n";
 // cout << std::setfill(' ') << std::setw(10) << left << "u" << u << endl;
//  cout << std::setfill(' ') << std::setw(10) << left << "S2" << S2_result << endl;
 // cout << "." << endl << endl;

//  mpfr::mpreal u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
 // cout<<"S4*******************************************************************************"<<endl;
 // mpfr::mpreal a = S4(x, u);
 // cout<<endl<<endl<<"slowS4*******************************************************************************"<<endl;
//  mpfr::mpreal b = slowS4(x, u);
//  cout<<"u         "<<u<<endl;
 // cout<<"S4        "<<a<<endl;
 // cout<<"Slow S4   "<<b<<endl;
//  cout<<"Diffrence "<<a - b<<endl;

 //   mpfr::mpreal a = psi(x);
//    mpfr::mpreal b = primetools::calculatePsiLongDouble(x);
 //   cout<<"Formula   "<<a<<endl;
 //   cout<<"Brute cal "<<b<<endl;
 //   cout<<"Diffrence "<<a - b<<endl;
  //  cout<<mpfr::mpreal::get_default_prec()<<endl;

 //   cout<<N(10000, 3.666721582566334971392540964529871417e+01, 1, 36)<<endl;

 //   long double u = cbrtl(static_cast<long double>(x)) * cbrtl(log(log(x))*log(log(x)));
 //   cout<<"u       = "<<u<<endl;
 //   cout<<"s4      = "<<S4(x, u)<<endl;
 //   cout<<"s4 slow = "<<slowS4(x, u)<<endl;

 //   auto before = clk.now();
  //  long double temp = psi(x);
  //  std::cout << "psi:     " << temp << std::endl;
  //  interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(clk.now() - before));
 //   before = clk.now();
  //  long double temp2 = primetools::calculatePsiLongDouble(x);
 //   std::cout << "slowPsi: " << temp2 << std::endl;
 //   interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(clk.now() - before));
  //  cout << "psi - slowPsi = " << temp - temp2 << std::endl;
  //  std::cout << std::endl;

  return 0;
}
