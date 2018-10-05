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
   mpfr::mpreal maxPsi = 0.0;
   mpfr::mpreal tmpPsi = 0.0;
   long long prime = 0;
   long long start = 19000000000;
   long long end = 20000000000;
   setupEnvironment();
   for(long long i = start; i < end; ++i) {
      tmpPsi = higherPsi(i);
      tmpPsi = (tmpPsi - i)/i;

      if(tmpPsi > maxPsi) {
	       maxPsi = tmpPsi;
	       prime = i;
      }

   }
   cout<<maxPsi<<" at prime "<<prime<<endl;
  return 0;
}
