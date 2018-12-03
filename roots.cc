#include <iostream>
#include <cmath>
#include <primesieve.hpp>
#include <primecount.hpp>
#include "./include/mpreal.h"

bool isPrime(const mpfr::mpreal, primesieve::iterator&);

int main() {
   mpfr::mpreal x = 211;
   mpfr::mpreal tempAns;
   std::vector<mpfr::mpreal> primePowers;
   primesieve::iterator it;
   
   for (mpfr::mpreal j = 1; j < 100000; ++j) {
      for (int i = 1; i < 20; ++i) {
	 tempAns = root(j, i);
	 if(tempAns == floor(tempAns))
	    if(isPrime(tempAns, it))
//	       std::cout<<j<<" is a prime power"<<std::endl;
	       primePowers.push_back(j);
      }
   }
   std::cout<<primePowers.size()<<std::endl;
   return 0;
}

bool isPrime(const mpfr::mpreal x, primesieve::iterator &it) {
   uint64_t y = static_cast<uint64_t>(x);
   //primesieve::iterator it;
   it.skipto(y-1);
//   std::cout<<"x = "<<x<<" and x -1 = "<<x-1<<std::endl;
   uint64_t prime = it.next_prime();
//   std::cout<<prime<<std::endl;
   if(prime == x)
      return true;
   else
      return false;
}
