#include "Consecutive.h"

mpfr::mpreal& Consecutive::operator[] (const size_t a) {
   return data[loc[a]];
}

mpfr::mpreal Consecutive::operator[] (const size_t a) const {
   return data[loc[a]];
}

size_t Consecutive::size() const {
   return loc.size();
}

size_t Consecutive::internalSize() const {
   return data.size();
}

bool Consecutive::self(const size_t a) const {
   return isSelf[a];
}

void Consecutive::push_back(const mpfr::mpreal& a) {
   isSelf.push_back(true);
   loc.push_back(data.size());
   data.push_back(a);
}

void Consecutive::tie_back() {
   isSelf.push_back(false);
   loc.push_back(data.size() - 1);
}
