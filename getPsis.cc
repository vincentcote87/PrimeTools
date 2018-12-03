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
    long long start = 10000000000000;
   long long end = 10686474590000;

   long long prime = 0;
   mpfr::mpreal maxPsi = 0.0;
   mpfr::mpreal tempPsi = 0.0;
   
   for(long long i = start; i < end; ++i) {
      tempPsi = higherPsi(i);
      tempPsi = (tempPsi - i) / i;
      if(tempPsi > maxPsi){
	 maxPsi = tempPsi;
	 prime = i;
      }

   }
   cout<<"M0 = "<<maxPsi<<" at prime "<<prime<<endl;
   return 0;
}
