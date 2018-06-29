#ifndef N_HPP
#define N_HPP
#include <cassert>
#include <iostream>
#include <cmath>
#include <cassert>
#include <cfenv>
#include <algorithm>
#include <vector>
typedef long long integer;
typedef long double rational;
static integer N(const integer x, const long double u, const integer l, const integer k);
static integer bruteN(const integer x, const rational u, const integer l, const integer k);
#endif

static integer bruteN(const integer x, const rational u, const integer l, const integer k) {
  assert(x < 10000000000000000);
  assert(l < 10000000000000000);
  const integer L2 = static_cast<long double>(x)/(u*(long double) l); //deliberate floor
   const auto roundEnv = std::fegetround();
   std::fesetround(FE_TONEAREST);
   const integer L1 = ((long long) std::sqrt(((long double) x)/((long double) l))) + 1; //deliberate floor of sqrt. can replace with a pure flooring integer sqrt later
   std::fesetround(roundEnv);
   integer count = 0;
   std::vector<integer> special;
   if(l == 1 && k == 36) {
     std::cout<<"low: "<<L1<<" high: "<<L2<<std::endl;
   }
   for (integer m = L1; m <= L2; ++m) {
     if (         k == static_cast<long long>(static_cast<long double>(x)/((long double) l*m))         ) {
        ++count;
        special.push_back(m);
      }
   }
   integer otherCount = N(x, u, l, k);
   if (count != otherCount) {
     std::cout << "bruteN's count: " << count << std::endl;
     std::cout << "N's count: " << otherCount <<std::endl;
     std::cout<<"x: "<<x<<" u: "<<u<<" l: "<<l<<" k: "<<k<<std::endl;
     std::cout << "m: ";
     for (auto i = special.begin(); i != special.end(); ++i) {
       std::cout << *i << ", ";
     }
     std::cout<<std::endl<<std::endl;
   }
   return count;
}

static integer N(const integer x, const long double u, const integer l, const integer k) {
   assert(x < 10000000000000000);
   assert(l < 10000000000000000);
   const integer L2 = static_cast<long double>(x)/(u*(long double) l); //deliberate floor
   const auto roundEnv = std::fegetround();
   std::fesetround(FE_TONEAREST);
   const integer L1 = ((long long) std::sqrt(((long double) x)/((long double) l))) + 1; //deliberate floor of sqrt. can replace with a pure flooring integer sqrt later
   std::fesetround(roundEnv);
   const integer M2 = x/(l*k); //deliberate floor
   const integer M1 = (x/(l*(k+1))) + 1; //deliberate floor of division
   if (M1 > M2)
      return 0;
   //std::cout << "L1: " << L1 << "; L2: " << L2 << "; M1: " << M1 << "; M2: " << M2 << std::endl;
   const integer high = std::min(L2,M2);
   const integer low = std::max(L1,M1);
   if (high < low)
      return 0;
   return high - low + 1; //inclusive count of consecutive integers from low through high
}
