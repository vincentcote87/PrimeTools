#ifndef PSITOOLS_H
#define PSITOOLS_H
#include <iostream>
#include <cmath>
#include <iomanip>
#include <primesieve.hpp>
#include <primecount.hpp>
#include <climits>
#include "B2.h"
#include "Primetools.h"
#include "N.hpp"

typedef uint64_t natural;
typedef long long integer;
long double T(long double);
mpfr::mpreal psi_work(uint64_t);
mpfr::mpreal psi(uint64_t);
mpfr::mpreal S1(uint64_t, mpfr::mpreal);
mpfr::mpreal S2(uint64_t, mpfr::mpreal);
mpfr::mpreal S3(uint64_t, mpfr::mpreal);
long long S3_B(uint64_t, mpfr::mpreal, uint64_t);
mpfr::mpreal S3_A(uint64_t, mpfr::mpreal, uint64_t);
mpfr::mpreal S4(uint64_t, mpfr::mpreal);
mpfr::mpreal S4a(uint64_t, mpfr::mpreal, mpfr::mpreal);
mpfr::mpreal S4a_innerLoop(uint64_t, mpfr::mpreal, uint64_t, mpfr::mpreal);
mpfr::mpreal S4b(uint64_t, mpfr::mpreal, mpfr::mpreal);
mpfr::mpreal S4b_innerSum(uint64_t, mpfr::mpreal, uint64_t, mpfr::mpreal);
// uint64_t pow(uint64_t, uint64_t);
long long mobius(long long);
long long mobius_work(long long);
void mobius_setup();
void psi_setup();
void setupEnvironment();

mpfr::mpreal slowS4(uint64_t x, mpfr::mpreal u);
mpfr::mpreal slowS4_inner(uint64_t x, mpfr::mpreal u, uint64_t l, mpfr::mpreal psiOfU);
#endif //PSITOOLS_H

static B2Class B2;
static const long double PI = 3.141592653589793238462643383279L;
static const int J = 10;

static const uint64_t mobiusCutoff = 1000001;
static long long *mobiusTable;

static const size_t cutoff = 10000000; //4294967295
static mpfr::mpreal *psiTable;
