#ifndef B2_H
#define B2_H
#include <cstddef>
class B2Class {
private:
   static const int SIZE = 20;
   int numerator[SIZE] = {1, 1, -1, 1, -1, 5, -691, 7, -3617, 43867, -174611};
   int denominator[SIZE] = {1, 6, 30, 42, 30, 66, 2730, 6, 510, 798, 330};
public:
   unsigned long long size() const;
   long double operator[] (const unsigned long long i) const;
};
#endif

unsigned long long B2Class::size() const {
      return SIZE;
}
long double B2Class::operator[] (const unsigned long long i) const {
  return numerator[i]/denominator[i];
}
