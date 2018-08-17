#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"
#include "InterpretClock.h"
#include <exception>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
	// std::cout << "About to initialize a dummy mpfr::mpreal...";
	// try {
	// 	mpfr::mpreal solo = 2;
	// 	std::cout << "SUCCESS";
	// } catch (std::exception e) {
	// 	std::cout << "FAILURE";
	// }
	// std::cout << std::endl;
  setupEnvironment();
	cout<<psi_work(100000)<<endl;
	cout<<psi_work(200000)<<endl;
	cout<<psi_work(1000000)<<endl;

  // uint64_t x;
  std::chrono::steady_clock clk;
  // if(argc == 2)
  //   x = std::stoll(argv[1]);
  // else {
  //   x = 100;
  //   cout<<"default value of x set at "<<x<<endl;
  // }

  std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> p1, p2;
  // for (long long i = 10; i <= 1000000000000000; i*=10) {
  // 	 std::cout << i << std::endl;
  // 	 x = i;
  //    p1 = clk.now();
  //    mpfr::mpreal temp = psi_work(x);
  //    cout << temp << endl;
  //    p2 = clk.now();
  //    interpretClk(p2 - p1);
  //    std::cout << "     Finished Execution" << std::endl;
  // }

	// for(long long i = 1000000; i <= 5000000; i *= 10) {
	// 	for(long long j = 1; j < 10; ++j) {
	// 		p1 = clk.now();
	// 		std::cout<<setprecision(1)<<std::scientific<<static_cast<long double>(i * j)<<" ";
	// 		std::cout<<std::setprecision(30)<<psi_work(i * j)<<" ";
	// 		p2 = clk.now();
	// 		interpretClk(p2 - p1);
	// 	}
	// }
  return 0;
}
