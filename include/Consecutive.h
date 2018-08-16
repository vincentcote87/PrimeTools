#ifndef CONSECUTIVE_H
#define CONSECUTIVE_H

#include <vector>
#include <mpreal.h>

class Consecutive {
  private:
   std::vector<mpfr::mpreal> data;
   std::vector<size_t> loc;
   long long offset;
   size_t mirageCliff;
   size_t mirageSize; //for thread safety
  public:
    Consecutive();
   mpfr::mpreal& operator[] (const size_t);
   mpfr::mpreal operator[] (const size_t) const;
   mpfr::mpreal& getData (const size_t);
   mpfr::mpreal getData (const size_t) const;
   size_t size() const;
   size_t firstX() const;
   size_t internalSize() const;
   void push_back(const mpfr::mpreal&);
   void tie_back();
   void setOffset(const long long);
   void clear();
};

#endif CONSECUTIVE_H
