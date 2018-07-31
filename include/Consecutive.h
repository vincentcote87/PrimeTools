#ifndef CONSECUTIVE_H
#define CONSECUTIVE_H

#include <vector>
#include <mpreal.h>

class Consecutive {
  private:
   std::vector<mpfr::mpreal> data;
   std::vector<size_t> loc;
   std::vector<bool> isSelf;
  public:
   mpfr::mpreal& operator[] (const size_t);
   mpfr::mpreal operator[] (const size_t) const;
   size_t size() const;
   size_t internalSize() const;
   bool self(const size_t) const;
   void push_back(const mpfr::mpreal&);
   void tie_back();
};

#endif CONSECUTIVE_H
