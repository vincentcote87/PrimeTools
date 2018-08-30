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

	uint64_t x;

	if(argc == 2){
    x = std::stoll(argv[1]);
	} else {
    x = 1;
		cout<<"Default values used for Max of x with "<<x<<endl;
  }

	setupEnvironment();
	cout<<"Psi("<<x<<") = "<<psi_work(x)<<endl;
	// cout<<higherTheta(10000000)<<endl;
	// for(uint64_t i = 10000000000000; i < 50000000000000; i += 40000000000) {
	// 	cout<<"psi("<<i<<") = "<<higherPsi(i)<<endl;
	// }
  return 0;
}
