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
long double psi_work(uint64_t);
long double psi(uint64_t);
long double S1(uint64_t, long double);
long double S2(uint64_t, long double);
long double S3(uint64_t, long double);
long long S3_B(uint64_t, long double, uint64_t);
long double S3_A(uint64_t, long double, uint64_t);
long double S4(uint64_t, long double);
long double S4a(uint64_t, long double, long double);
long double S4a_innerLoop(uint64_t, long double, uint64_t, long double);
long double S4b(uint64_t, long double, long double);
long double S4b_innerSum(uint64_t, long double, uint64_t, long double);
// uint64_t pow(uint64_t, uint64_t);
long long mobius(long long);
long long mobius_work(long long);
void mobius_setup();
void psi_setup();
void setupEnvironment();

long double slowS4(uint64_t x, long double u);
long double slowS4_inner(uint64_t x, long double u, uint64_t l, long double psiOfU);
#endif //PSITOOLS_H

static B2Class B2;
static const long double PI = 3.141592653589793238462643383279L;
static const int J = 10;

static const uint64_t mobiusCutoff = 1000001;
static long long *mobiusTable;

static const size_t cutoff = 10000000; //4294967295
static long double *psiTable;
