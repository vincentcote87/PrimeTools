#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"
#include "InterpretClock.h"
#include "HigherPsi.h"
#include <exception>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
	
	setupEnvironment();
	long long start = 10000000;
	long long end = 100000000;

	for(long long i = start; i < end; ++i) {
		cout<<higherPsi(i)<<endl;
	}

  return 0;
}
