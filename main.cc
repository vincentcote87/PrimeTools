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

vector<mpfr::mpreal> maxK(const uint64_t, const uint64_t);

int main(int argc, char* argv[]) {

	setupEnvironment();
	// cout<<primetools::calculateThetaWithPsi(100000000)<<endl;
	// for(uint64_t i = 0; i < 1000000; ++i) {
	// 	cout<<"theta at "<<i<<" = "<<higherTheta(i)<<endl;
	// }

	vector<mpfr::mpreal> myVec =  maxK(1, 500000000);

	for(int i = 0; i < myVec.size(); ++i) {
		cout<<"M"<<i<<" = "<<myVec[i]<<endl;
	}

	// std::cout << "About to initialize a dummy mpfr::mpreal...";
	// try {
	// 	mpfr::mpreal solo = 2;
	// 	std::cout << "SUCCESS";
	// } catch (std::exception e) {
	// 	std::cout << "FAILURE";
	// }
	// std::cout << std::endl;
  // setupEnvironment();
  // uint64_t x;
  // std::chrono::steady_clock clk;
  // if(argc == 2)
  //   x = std::stoll(argv[1]);
  // else {
  //   x = 100;
  //   cout<<"default value of x set at "<<x<<endl;
  // }

  // std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> p1, p2;
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
	//
	// for(long long i = 1000000; i <= 1000000000000000; i *= 10) {
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

vector<mpfr::mpreal> maxK(const uint64_t lowerBound, const uint64_t upperBound){
	vector<mpfr::mpreal> M;
	uint64_t n = upperBound + 1;
	mpfr::mpreal theta = 0.0;
	mpfr::mpreal logOfp = 0.0;
	mpfr::mpreal result = 0.0;

	primesieve::iterator it;
	it.skipto(lowerBound);
	uint64_t Pn = it.next_prime();
	uint64_t PnPlusOne = it.next_prime();


	for(int i = 0; i < 5; ++i) {
		M.push_back(0.0);
	}

	for (; PnPlusOne <= n; PnPlusOne = it.next_prime()) {
		theta = higherTheta(PnPlusOne);
		logOfp = mpfr::log(Pn);
		for(long long k = 0; k < 5; ++k) {
			result = ((theta - mpfr::mpreal{Pn})*mpfr::pow(logOfp, mpfr::mpreal{k}, MPFR_RNDN)) / mpfr::mpreal{Pn};
			if(result > M[k]){
				// cout<<"For M"<<k<<" Pn = "<<Pn<<endl;
				M[k] = result;
			}
		}
		Pn = PnPlusOne;
	}

	//
	// uint64_t PnPlusOne = it.next_prime();
	//
	// cout<<prime<<" and "<<it.next_prime()<<std::endl;
	// for (; prime <= n; prime = it.next_prime()) {
	// 	cout<<prime<<endl;
	// }
	return M;
}
