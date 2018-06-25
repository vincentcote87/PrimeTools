#include "B2.h"

unsigned long long B2Class::size() const {
      return SIZE;
}
long double B2Class::operator[] (const unsigned long long i) const {
  return numerator[i]/denominator[i];
}
