#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"
#include "InterpretClock.h"
#include "bounds.h"
#include <exception>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	setupEnvironment();
	uint64_t lBound;
	uint64_t uBound;
	uint64_t multiplyer = 2;
	uint64_t base;
	mpfr::mpreal givenPsi;

	cout<<primetools::calculateThetaLongDouble(1,100810747)<<endl;
	cout<<primetools::calculateThetaWithPsi(100810747)<<endl;
	if(argc == 2){
		lBound = 1;
    uBound = std::stoll(argv[1]);
		givenPsi = 0.0;
	}
	else if(argc == 3) {
		lBound = std::stoll(argv[1]);
		uBound = std::stoll(argv[2]);
		givenPsi = 0.0;
	}
	else if(argc >= 4) {
		lBound = std::stoll(argv[1]);
		uBound = std::stoll(argv[2]);
		givenPsi = argv[3];
	}
  else {
    lBound = 1;
		uBound = 100000;
		cout<<"Default values used for Max of x with "<<lBound<<" < x <= "<<uBound<<endl;
  }

	cout<<"Given psi is "<<givenPsi<<endl;
	// cout<<primetools::calculateThetaWithPsi(100000000)<<endl;
	// for(uint64_t i = 0; i < 1000000; ++i) {
	// 	cout<<"theta at "<<i<<" = "<<higherTheta(i)<<endl;
	// }

  std::chrono::steady_clock clk;
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> p1, p2;
	bool isRunning = true;
	bool interval = false;
	vector<mpfr::mpreal> overallMax;
	// vector<mpfr::mpreal> myVec;
	overallMax.resize(12);

	// for(uint64_t i = 10; i <= 1000000000000000; i *= 10) {
	// 	for(uint64_t j = 1; j < 10; ++j) {
	// 		if(j != 9){
	// 			myVec =  maxK(i*j, i*(j+1), 0);
	// 			cout<<"Showing results for Max of x with "<<i*j<<" < x <= "<<i*(j+1)<<endl;
	// 		}
	// 		else {
	// 			myVec =  maxK(i*j, i*10, 0);
	// 			cout<<"Showing results for Max of x with "<<i*j<<" < x <= "<<i*10<<endl;
	// 		}
	// 		for(int i = 0; i < myVec.size()/2; ++i) {
	// 			cout<<std::scientific<<"M"<<i<<" = "<<myVec[i]<<" with P = "<<std::fixed<<myVec[i+6]<<endl;
	// 		}
	// 	}
	// }

	// cout<<primetools::calculateThetaWithPsi(1000000, 9.995865974956329220330615330113e+05)<<endl;
	// cout<<primetools::calculateThetaWithPsi(1000000000000)<<endl;
	// overallMax = maxK(100000000, 1000000000);
	// for(int i = 0; i < overallMax.size()/2; ++i) {
	// 	cout<<std::scientific<<"Max overall M"<<i<<" = "<<overallMax[i]<<" with P = "<<std::fixed<<overallMax[i+6]<<endl;
	// }
	// base = lBound;
	// while(isRunning) {
	//
		p1 = clk.now();
		vector<mpfr::mpreal> myVec = maxK(lBound, uBound);
		p2 = clk.now();
		cout<<"Showing results for Max of x with "<<lBound<<" < x <= "<<uBound<<endl;
		for(int i = 0; i < myVec.size()/2; ++i) {
			cout<<std::scientific<<"M"<<i<<" = "<<myVec[i]<<" with P = "<<std::fixed<<myVec[i+6]<<endl;
			if(myVec[i] > overallMax[i]){
				overallMax[i] = myVec[i];
				overallMax[i+5] = myVec[i+5];
			}
		}
		// lBound = uBound;
		// uBound = base * multiplyer;
		// uBound *= multiplyer;
		// multiplyer++;
		// if(multiplyer > 10) {
		// 	multiplyer = 2;
		// 	base *= 10;
		//
		// }
		// interpretClk(p2 - p1);
		// cout<<endl;
		// lBound = uBound;
		// if(interval)
		// 	uBound *= 2;
		// else
		// 	uBound *= 5;
		// interval = !interval;
		//
	// 	if(uBound >= 10000000000000)
	// 		isRunning = false;
	// }
		//
		// for(int i = 0; i < overallMax.size()/2; ++i) {
		// 	cout<<std::scientific<<"Max overall M"<<i<<" = "<<overallMax[i]<<" with P = "<<std::fixed<<overallMax[i+5]<<endl;
		// }


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
