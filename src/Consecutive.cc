#include "Consecutive.h"

Consecutive::Consecutive()
   : data{}, loc{}, mirageCliff{0}, mirageSize{0}
{}

mpfr::mpreal& Consecutive::operator[] (const size_t a) {
   return data[loc[a-mirageCliff]];
}

mpfr::mpreal Consecutive::operator[] (const size_t a) const {
   return data[loc[a-mirageCliff]];
}

mpfr::mpreal& Consecutive::getData (const size_t a) {
   return data[a];
}

mpfr::mpreal Consecutive::getData (const size_t a) const {
   return data[a];
}

size_t Consecutive::size() const {
  return mirageSize;
   //return loc.size();
}

size_t Consecutive::internalSize() const {
   return data.size();
}

void Consecutive::push_back(const mpfr::mpreal& a) {
   loc.push_back(data.size());
   data.push_back(a);
   ++mirageSize;
}

void Consecutive::tie_back() {
   loc.push_back(data.size() - 1);
   ++mirageSize;
}

void Consecutive::clear() {
   data.clear();
   loc.clear();
   mirageCliff = 0;
   mirageSize = 0;
}

size_t Consecutive::firstX() const {
   return mirageCliff;
}

void Consecutive::setOffset(const long long a) {
   mirageCliff = a;
}
