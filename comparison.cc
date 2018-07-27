#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "InterpretClock.h"
#include "N.h"
#include <exception>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
	std::cout << "About to initialize a dummy mpfr::mpreal...";
	try {
		mpfr::mpreal solo = 2;
		std::cout << "SUCCESS";
	} catch (std::exception e) {
		std::cout << "FAILURE";
	}
	std::cout << std::endl;
  setupEnvironment();
  uint64_t x;
  std::chrono::steady_clock clk;
  if(argc == 2)
    x = std::stoll(argv[1]);
  else {
    x = 100;
    cout<<"default value of x set at "<<x<<endl;
  }
  
  
	 std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> p1, p2, p3, p4;
  
	 p1 = clk.now();
	 mpfr::mpreal ans = primetools::calculatePsiNoTheta(x);
	p2 = clk.now();
	 mpfr::mpreal an2 = primetools::calculatePsiLongDouble(x);
	 p3 = clk.now();
	 mpfr::mpreal an3 = psi_work(x);
	 p4 = clk.now();
	 std::cout << "Powered Psi: " << ans << std::endl;
	 std::cout << "Theta Psi:   " << an2 << std::endl;
	 std::cout << "A Psi:       " << an3 << std::endl;
  
	 std::cout << "Powered Psi: ";
	 interpretClk(p2 - p1);
	 std::cout << "Theta Psi:   ";
	 interpretClk(p3 - p2);
	 std::cout << "A Psi:       ";
	 interpretClk(p4 - p3);


  std::cout << "     Finished Execution" << std::endl;
  return 0;
}
