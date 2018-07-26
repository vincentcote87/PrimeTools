#ifndef S3_H
#define S3_H
#include "Environment.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <primesieve.hpp>
#include <primecount.hpp>
#include <climits>
#include "mpreal.h"
#include "PsiTools.h"
#include <utility>

#include "mobius.h"

mpfr::mpreal S3(uint64_t, mpfr::mpreal);
long long S3_B(uint64_t, mpfr::mpreal, uint64_t);
mpfr::mpreal S3_A(uint64_t, mpfr::mpreal, uint64_t);
uint64_t floor_pow(uint64_t, uint64_t);

#endif
