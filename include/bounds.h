#ifndef BOUNDS_H
#define BOUNDS_H
#include <vector>
#include "mpreal.h"
#include "PsiTools.h"
#include "Primetools.h"

std::vector<mpfr::mpreal> maxK(const uint64_t, const uint64_t);

std::vector<mpfr::mpreal> maxK(const uint64_t, const uint64_t, const mpfr::mpreal);

#endif //BOUNDS_H
