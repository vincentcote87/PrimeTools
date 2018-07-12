#ifndef B2_H
#define B2_H
#include "Environment.h"
#include "mpreal.h"
#include <cstddef>
class B2Class {
private:
   static const int SIZE = 12;
   // Source: http://numbers.computation.free.fr/Constants/Miscellaneous/bernoulli.html
   int numerator[SIZE] =   {1, 1, -1,  1, -1,  5, -691, 7, -3617, 43867, -174611, 854513};
   int denominator[SIZE] = {1, 6, 30, 42, 30, 66, 2730, 6,   510,   798,     330,    138};
   mpfr::mpreal* bernoulli;
public:
   B2Class ();
   ~B2Class ();
   unsigned long long size() const;
   mpfr::mpreal operator[] (const unsigned long long i) const;
};
#endif
