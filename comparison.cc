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
	mpfr::mpreal valE = "2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901157383418793070215408914993488416750924476146066808226480016847741185374234544243710753907774499206955170276183860626133138458300075204493382656029760";
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
	 std::cout << "Difference:  " << an3 - an2 << std::endl;
	 std::cout << "Exp:         " << pow(abs(an3 - an2, MPFR_RNDN), valE, MPFR_RNDN) << std::endl;
  
	 std::cout << "Powered Psi: ";
	 interpretClk(p2 - p1);
	 std::cout << "Theta Psi:   ";
	 interpretClk(p3 - p2);
	 std::cout << "A Psi:       ";
	 interpretClk(p4 - p3);


  std::cout << "     Finished Execution" << std::endl;
  return 0;
}
